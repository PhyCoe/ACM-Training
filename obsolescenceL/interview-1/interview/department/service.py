# coding: utf-8
"""
DepartmentService
"""

from interview.models import Employee, Department, db, EmployeeDepartmentRelation
from interview.flask import cli

class DepartmentService(object):

    def is_user_in_department(self, employee_id, department_id) -> bool:
        if cli.exists('employee_' + str(employee_id) + '_department') == 0:
            if Employee.query.get(employee_id) is None:
                return False
            department_of_employee = EmployeeDepartmentRelation.query.filter_by(employee_id=employee_id).first()
            if department_of_employee is None:
                return False
            direct_department_id = department_of_employee.department_id
            cli.set('employee_' + str(employee_id) + '_department', department_id)
        else:
            direct_department_id = int(cli.get('employee_' + str(employee_id) + '_department'))
        parents = self.get_department_parents(direct_department_id)
        return department_id in parents

    def get_department_parents(self, department_id):
        ans = []
        ans.append(department_id)
        department = Department.query.filter_by(id=department_id).first()
        while department is not None:
            if department.parent_id != 0:
                ans.append(department.parent_id)
            department = Department.query.filter_by(id=department.parent_id).first()
        return ans
