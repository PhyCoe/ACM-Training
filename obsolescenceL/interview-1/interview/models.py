# coding: utf-8
"""
models
"""

from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.dialects.mysql import BIGINT, VARCHAR
from .flask import app

db = SQLAlchemy(app)

class Employee(db.Model):
    id = db.Column(BIGINT(unsigned=True), primary_key=True)
    name = db.Column(VARCHAR(64), nullable=False)

    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return '<Employee %r, %r>\n' %(self.id, self.name)


class Department(db.Model):
    id = db.Column(BIGINT(unsigned=True), primary_key=True)
    name = db.Column(VARCHAR(64), nullable=False)
    parent_id = db.Column(BIGINT(unsigned=True), nullable=False)
    leader = db.relationship('Employee', backref=db.backref('department', lazy='dynamic'))
    leader_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('employee.id'))

    def __init__(self, parent_id, name, leader_id):
        self.parent_id = parent_id
        self.name = name
        self.leader_id = leader_id

    def __repr__(self):
        return '<Department(id, parent_id, name, leader_id) (%r, %r, %r, %r)>\n' %(self.id, self.parent_id, self.name, self.leader_id)


class EmployeeDepartmentRelation(db.Model):
    id = db.Column(BIGINT(unsigned=True), primary_key=True)
    employee = db.relationship('Employee', backref=db.backref('employeedepartmentrelation', lazy='dynamic'))
    employee_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('employee.id'))
    department = db.relationship('Department', backref=db.backref('employeedepartmentrelation', lazy='dynamic'))
    department_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('department.id'))

    def __init__(self, employee_id, department_id):
        self.employee_id = employee_id
        self.department_id = department_id

    def __repr__(self):
        return '<E_D_Relation(id, employee_id, department_id, is_leader) (%r, %r, %r, %r)>\n' %(self.id, self.employee_id, self.department_id, self.is_leader)


class Resource(db.Model):
    id = db.Column(BIGINT(unsigned=True), primary_key=True)
    name = db.Column(VARCHAR(64), nullable=False)

    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return '<Resource(id, name) (%r, %r)>\n' %(self.id, self.name)


class Permission(db.Model):
    id = db.Column(BIGINT(unsigned=True), primary_key=True)
    name = db.Column(VARCHAR(64), nullable=False)
    action = db.Column(VARCHAR(32), nullable=False)
    resource = db.relationship('Resource', backref=db.backref('permission', lazy='dynamic'))
    resource_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('resource.id'))

    def __init__(self, name, resource_id, action):
        self.name = name
        self.resource_id = resource_id
        self.action = action

    def __repr__(self):
        return '<Permission(id, name, resource_id, action) (%r, %r, %r, %r)>\n' %(self.id, self.name, self.resource_id, self.action)


class DepartmentPermissionRelation(db.Model):
    id = db.Column(BIGINT(unsigned=True), primary_key=True)
    department = db.relationship('Department', backref=db.backref('departmentpermissionrelation', lazy='dynamic'))
    department_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('department.id'))
    permission = db.relationship('Permission', backref=db.backref('departmentpermissionrelation', lazy='dynamic'))
    permission_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('permission.id'))

    def __init__(self, department_id, permission_id):
        self.department_id = department_id
        self.permission_id = permission_id

    def __repr__(self):
        return '<D_P_Relation(id, department_id, permission_id) (%r, %r, %r)>\n' %(self.id, self.department_id, self.permission_id)


class LeaderPermissionRelation(db.Model):
    id = db.Column(BIGINT(unsigned=True), primary_key=True)
    leader = db.relationship('Employee', backref=db.backref('leaderpermissionrelation', lazy='dynamic'))
    leader_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('employee.id'))
    permission = db.relationship('Permission', backref=db.backref('leaderpermissionrelation', lazy='dynamic'))
    permission_id = db.Column(BIGINT(unsigned=True), db.ForeignKey('permission.id'))

    def __init__(self, leader_id, permission_id):
        self.leader_id = leader_id
        self.permission_id = permission_id

    def __repr__(self):
        return '<L_R_Relation(id, leader_id, permission_id) (%r, %r, %r)>\n' %(self.id, self.leader_id, self.permission_id)
