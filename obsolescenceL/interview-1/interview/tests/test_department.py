# coding: utf-8
"""
tear_department
"""

from unittest import TestCase
from interview.models import Employee, Department, db, EmployeeDepartmentRelation
from interview.department.service import DepartmentService

class TestDepartment(TestCase):

    def setUp(self):
        db.create_all()
        e1 = Employee('aa')
        e2 = Employee('bb')
        e3 = Employee('cc')
        db.session.add(e1)
        db.session.add(e2)
        db.session.add(e3)
        db.session.commit()

        d1 = Department(0, 'a', 1)
        d2 = Department(1, 'b', 3)
        d3 = Department(2, 'c', 2)
        db.session.add(d1)
        db.session.add(d2)
        db.session.add(d3)
        db.session.commit()

        r1 = EmployeeDepartmentRelation(2, 3)
        r2 = EmployeeDepartmentRelation(3, 2)
        r3 = EmployeeDepartmentRelation(1, 1)
        db.session.add(r1)
        db.session.add(r2)
        db.session.add(r3)
        db.session.commit()

    def tearDown(self):
        db.session.remove()
        db.drop_all()

    def test_is_user_in_department(self):
        s = DepartmentService()

        #测试员工1是否在部门0,1,2,3中
        assert s.is_user_in_department(1, 0) == False
        #部门0不存在,返回false
        assert s.is_user_in_department(1, 1) == True
        #员工1在部门1中,返回true
        assert s.is_user_in_department(1, 2) == False
        #员工1不在部门2中,返回false
        assert s.is_user_in_department(1, 3) == False
        #员工1不在部门3中,返回false

        #测试员工2是否在部门0,1,2,3中
        assert s.is_user_in_department(2, 0) == False
        #部门0不存在,返回false
        assert s.is_user_in_department(2, 1) == True
        #员工2在部门3中,部门3隶属于部门2,部门2隶属于部门1,员工2在部门1中,返回true
        assert s.is_user_in_department(2, 2) == True
        #员工2在部门3中,部门3隶属于部门2,员工2在部门2中,返回true
        assert s.is_user_in_department(2, 3) == True
        #员工2在部门3中,返回true

        #测试员工0是否在部门3中
        assert s.is_user_in_department(0, 3) == False
        #员工0不存在,返回false

        #测试员工4是否在部门4中
        assert s.is_user_in_department(4, 4) == False
        #员工4不存在,返回false
