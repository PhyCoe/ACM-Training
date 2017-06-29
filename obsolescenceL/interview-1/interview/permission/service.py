# coding: utf-8
"""
PermissionService
"""

from typing import Dict
from interview.models import Employee, Department, db, EmployeeDepartmentRelation
from interview.models import Resource, Permission, DepartmentPermissionRelation
from interview.models import LeaderPermissionRelation
from interview.flask import cli
from interview.department.service import DepartmentService

class PermissionService(object):

    def get_user_permissions(self, employee_id, resource_id):
        if cli.exists('employee_' + str(employee_id) + '_department') == 0:
            if Employee.query.get(employee_id) is None:
                return []
            department_of_employee = EmployeeDepartmentRelation.query.filter_by(employee_id=employee_id).first()
            if department_of_employee is None:
                return []
            department_id = department_of_employee.department_id
            cli.set('employee_' + str(employee_id) + '_department', department_id)
            leader_id = department_of_employee.leader_id
            cli.set('department_' + str(department_id) + '_leader', leader_id)
        else:
            department_id = int(cli.get('employee_' + str(employee_id) + '_department'))
            leader_id = int(cli.get('department_' + str(department_id) + '_leader'))
        if cli.exists('resource_' + str(resource_id)) == 0:
            if Resource.query.get(resource_id) is None:
                return []
            else:
                cli.set('resource_' + str(resource_id), True)

        ans = []
        if leader_id == employee_id:
            ans.extend(self.get_leader_permission_list(leader_id, resource_id))
        ans.extend(self.get_department_permission_list(department_id, resource_id))
        ans.sort()
        return list(set(ans))

    def grant_permission_to_department(self, department_id, permission_id) -> bool:
        if cli.exists('department_' + str(department_id)) == 0:
            if Department.query.get(department_id) is None:
                return False
            else:
                cli.set('department_' + str(department_id), True)
        if cli.exists('permission_' + str(permission_id)) == 0:
            if Permission.query.get(permission_id) is None:
                return False
            else:
                cli.set('permission_' + str(permission_id), True)
        d_p_r = DepartmentPermissionRelation(department_id, permission_id)
        db.session.add(d_p_r)
        db.session.commit()
        return True

    def grant_permission_to_department_leaders(self, department_id, permission_id) -> bool:
        if cli.exists('department_' + str(department_id)) == 0:
            if Department.query.get(department_id) is None:
                return False
            else:
                cli.set('department_' + str(department_id), True)
        if cli.exists('permission_' + str(permission_id)) == 0:
            if Permission.query.get(permission_id) is None:
                return False
            else:
                cli.set('permission_' + str(permission_id), True)
        path = self.get_department_leaders(department_id)
        for x in path:
            db.session.add(LeaderPermissionRelation(x, permission_id))
        db.session.commit()
        return True

    def get_department_leaders(self, department_id):
        s = DepartmentService()
        path = s.get_department_parents(department_id)
        ans = []
        for x in path:
            if cli.exists('department_' + str(x) + '_leader') == 0:
                department = Department.query.filter_by(id=x).first()
                if department is not None:
                    leader_id = department.leader_id
                    cli.set('department_' + str(x) + '_leader', leader_id)
                    ans.append(leader_id)
            else:
                leader_id = int(cli.get('department_' + str(x) + '_leader'))
                ans.append(leader_id)
        return ans

    def get_leader_permission_list(self, leader_id, resource_id):
        permission_of_leader = LeaderPermissionRelation.query.filter_by(leader_id=leader_id).all()
        if permission_of_leader is None:
            return []
        ans = []
        for p_of_l in permission_of_leader:
            r_of_p = Permission.query.filter_by(id=p_of_l.permission_id).first()
            if r_of_p is not None:
                if r_of_p.resource_id == resource_id:
                    ans.append(r_of_p.id)
        return list(set(ans))

    def get_department_permission_list(self, department_id, resource_id):
        permission_of_department = DepartmentPermissionRelation.query.filter_by(department_id=department_id).all()
        if permission_of_department is None:
            return []
        ans = []
        for p_of_d in permission_of_department:
            r_of_p = Permission.query.filter_by(id=p_of_d.permission_id).first()
            if r_of_p is not None:
                if r_of_p.resource_id == resource_id:
                    ans.append(r_of_p.id)
        return list(set(ans))
