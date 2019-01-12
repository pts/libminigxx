#ifdef __cplusplus
extern "C" {
#endif

/* *_xptr variables are really size_t, but we want to avoid #include. */
void abort(void) __attribute__((noreturn));
void*/*_xptr*/ write(int fd, const void *buf, void *count_xptr);

void* __cxa_bad_cast(void) {
  (void)!write(2, "bad cast\n", (char*)0 + 9);
  abort();
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
