int create_redis_connect();
void close_redis_connect();
void sequence_incr(char *s);
unsigned long long int
sequence_reset(char *s, 
			unsigned long long int reset_value);
