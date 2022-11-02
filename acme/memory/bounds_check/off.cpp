

void * os_alloc(memsize size)
{

	return os_impl_alloc(size);


}


void * os_realloc(void * p, memsize size)
{

	return os_impl_realloc(p, size);

}


void os_free(void * p)
{

	return os_impl_free(p);

}

size_t os_size(void * p)
{

	return os_impl_size(p);

}




