#undef YUKA_EXPORT_
#ifdef __GNUC__
# define YUKA_EXPORT_ __attribute__((visibility ("default")))
#else
# define YUKA_EXPORT_
#endif
