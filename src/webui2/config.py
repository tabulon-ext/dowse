from redis import StrictRedis


redis_host = "127.0.0.1"
redis_storage_port = 6379
redis_volatile_port = 6378

redis_dynamic = 0
redis_storage = 2

RDYNA = StrictRedis(host=redis_host, port=redis_volatile_port,
                    db=redis_dynamic, decode_responses=True)
RSTOR = StrictRedis(host=redis_host, port=redis_storage_port,
                    db=redis_storage, decode_responses=True)
