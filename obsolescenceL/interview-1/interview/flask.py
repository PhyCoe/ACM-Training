# coding: utf-8
"""
"""
from flask import Flask
from interview.common.redis import get_redis_client
app = Flask('interview', instance_relative_config=True)
app.config.from_object('interview.config.common')
cli = get_redis_client()
