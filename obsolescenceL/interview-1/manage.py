# coding: utf-8
"""
"""


from flask_migrate import Migrate, MigrateCommand
from flask_script import Manager

from interview.models import db, app

Migrate(app, db)

manager = Manager(app)
manager.add_command('db', MigrateCommand)

if __name__ == '__main__':
    manager.run()
