# coding: utf-8
"""
redis
"""
from redis import StrictRedis

__cli = None


def get_redis_client():
    global __cli

    if __cli is None:
        from ..flask import app
        __cli = StrictRedis.from_url(app.config['REDIS_URI'])
        
    return __cli
