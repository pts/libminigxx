#ifdef __cplusplus
extern "C" {
#endif

/* *_xptr variables are really size_t, but we want to avoid #include. */
void abort(void) __attribute__((noreturn));
void*/*_xptr*/ write(int fd, const void *buf, void *count_xptr);
void *malloc(void *size_xptr);

static void* emulate_cc_new(void *size_xptr) {
  void *p = malloc(size_xptr);
  if (p == 0) {
    /* Don't use stdio (e.g. fputs), because that may want to allocate more
     * memory.
     */
    (void)!write(2, "out of memory\n", (char*)0 + 14);
    abort();
  }
  return p;
}

void* _Znwm /*operator new   amd64*/(void *size_xptr) __attribute__((alias("emulate_cc_new")));
void* _Znam /*operator new[] amd64*/(void *size_xptr) __attribute__((alias("emulate_cc_new")));
void* _Znwj /*operator new   i386*/(void *size_xptr) __attribute__((alias("emulate_cc_new")));
void* _Znaj /*operator new[] i386*/(void *size_xptr) __attribute__((alias("emulate_cc_new")));

#ifdef __cplusplus
}  /* extern "C" */
#endif
