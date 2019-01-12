#ifdef __cplusplus
extern "C" {
#endif

void free(void *ptr);

static void emulate_cc_delete(void* p) {
  free(p);
}

void  _ZdlPv/*operator delete  */(void* p) __attribute__((alias("emulate_cc_delete")));
void  _ZdaPv/*operator delete[]*/(void* p) __attribute__((alias("emulate_cc_delete")));

#ifdef __cplusplus
}  /* extern "C" */
#endif
