# coding: utf-8
"""
test_permission
"""

from unittest import TestCase
from interview.models import Employee, Department, db, EmployeeDepartmentRelation
from interview.models import Resource, Permission, DepartmentPermissionRelation
from interview.models import LeaderPermissionRelation
from interview.permission.service import PermissionService

class TestPermission(TestCase):

    def setUp(self):
        db.create_all()
        e1 = Employee('A')
        e2 = Employee('B')
        e3 = Employee('C')
        db.session.add(e1)
        db.session.add(e2)
        db.session.add(e3)
        db.session.commit()

        d1 = Department(0, 'company', 1)
        d2 = Department(1, 'IT', 3)
        d3 = Department(2, 'mobile IT', 2)
        db.session.add(d1)
        db.session.add(d2)
        db.session.add(d3)
        db.session.commit()

        e_d_r1 = EmployeeDepartmentRelation(2, 3)
        e_d_r2 = EmployeeDepartmentRelation(3, 3)
        e_d_r3 = EmployeeDepartmentRelation(1, 1)
        db.session.add(e_d_r1)
        db.session.add(e_d_r2)
        db.session.add(e_d_r3)
        db.session.commit()

        r1 = Resource('fingerprint')
        db.session.add(r1)
        db.session.commit()

        p1 = Permission('sign', 1, 'sign')
        p2 = Permission('enter', 1, 'enter')
        db.session.add(p1)
        db.session.add(p2)
        db.session.commit()

    def tearDown(self):
        db.session.remove()
        db.drop_all()

    def test_get_user_permissions(self):
        s = PermissionService()

        #测试员工2现有资源1的权限列表
        assert s.get_user_permissions(2, 1) == []
        #员工2目前没有资源1,返回[]

        #测试为部门1赋予权限1操作是否成功
        assert s.grant_permission_to_department(1, 1) == True
        #成功返回true

        #测试员工1现有资源1的权限列表
        assert s.get_user_permissions(1, 1) == [1]
        #员工1属于部门1,部门1的所有员工具有权限1,权限1的资源为资源1,返回[1]

        #测试员工2现有资源1的权限列表
        assert s.get_user_permissions(2, 1) == []
        #员工2目前没有资源1,返回[]

        #测试为部门3赋予权限1操作是否成功
        assert s.grant_permission_to_department(3, 1) == True
        #成功返回true

        #测试员工2现有资源1的权限列表
        assert s.get_user_permissions(2, 1) == [1]
        #员工2属于部门3,部门3的所有员工具有权限1,权限1的资源为资源1,返回[1]

        #测试为部门3的所有上级赋予权限2
        assert s.grant_permission_to_department_leaders(3, 2) == True
        #成功返回true

        #测试员工1现有资源1的权限列表
        assert s.get_user_permissions(1, 1) == [1, 2]
        #员工1是部门1的leader,部门3隶属于部门2,部门2隶属于部门1,员工1现有资源1的权限列表为[1,2],返回[1,2]

        #测试为部门3的所有上级赋予权限1
        assert s.grant_permission_to_department_leaders(3, 1) == True
        #成功返回true

        #测试员工1现有资源1的权限列表
        assert s.get_user_permissions(1, 1) == [1, 2]
        #员工1是部门1的leader,部门3隶属于部门2,部门2隶属于部门1,员工1现有资源1的权限列表为[1,2],返回[1,2]
