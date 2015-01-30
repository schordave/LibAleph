/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */
#if A_INCLUDE_MEM == 1
struct a_pool
{
    size_t size;
    size_t count;
};
#define a_p_data(b) ((a_str*)((char*)b + sizeof (struct a_pool)))
a_pool a_gc_new()
{
    a_pool pool;
    if ((pool = malloc(sizeof (struct a_pool) + sizeof (a_str) * A_MIN_STR_POOL_SIZE)))
    {
        pool->size = A_MIN_STR_POOL_SIZE;
        pool->count = 0;
    }
    return pool;
}
void a_gc_free(a_pool pool)
{
    a_str *e = a_p_data(pool);
    while (pool->count--)
        a_free(e[pool->count]);
    free(pool);
}
a_str a_gc_collect(a_pool *pool, a_str str)
{
    a_pool p = *pool;
    
    if (!str)
        return NULL;
    
    if (p->count+1 >= p->size)
    {
        a_pool new_pool = realloc(p, sizeof (struct a_pool) + sizeof (a_str) * p->size * 2);
        if (!new_pool)
        { /* if we can't get a bigger pool, we need to guarantee whatever was passed
             still gets cleaned up correctly. */
            a_free(str);
            return NULL;
        }
        *pool = new_pool;
        p = new_pool;
        p->size *= 2;
    }
    a_p_data(p)[p->count++] = str;
    return str;
}

#endif