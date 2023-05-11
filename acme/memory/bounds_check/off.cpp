

void* operating_system_memory_allocate(memsize size);
void* operating_system_memory_reallocate(void* p, memsize size);
void operating_system_memory_free(void* p);
memsize operating_system_memory_size(void* p);


void * __operating_system_memory_allocate(memsize size)
{

	return operating_system_memory_allocate(size);

}


void * __operating_system_memory_reallocate(void * p, memsize size)
{

	return operating_system_memory_reallocate(p, size);

}


void __operating_system_memory_free(void * p)
{

	return operating_system_memory_free(p);

}


memsize __operating_system_memory_size(void * p)
{

	return operating_system_memory_size(p);

}



