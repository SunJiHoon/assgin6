#ifndef DS_MONITORING_H
#define DS_MONITORING_H



//monitoring 구조체 정의
struct ds_monitoring {
    struct xarray *elements;
    unsigned long long total_counts;
    const struct ds_monitoring_operations *dm_ops;
};

struct ds_monitoring_operations {
	unsigned long (*get_index)(void *elem);
	const char * (*get_name)(void *elem);
	void (*print_elem)(
		unsigned long index,
		const char *name,
		unsigned long long count,
		int percentage
	);
};

struct ds_monitoring_elem {
	unsigned long key;
	char *name;
	unsigned long long count;
};

#define DEFINE_DS_MONITORING(name, get_idx_fn, get_name_fn, print_fn) \
	DEFINE_XARRAY(name##xarray); \
	DEFINE_DS_MONITORING_OPS(name, get_idx_fn, get_name_fn, print_fn); \
	struct ds_monitoring name = DS_MONITORING_INIT(name##xarray, name##_dm_ops);


#define DEFINE_DS_MONITORING_OPS(name, get_idx_fn, get_name_fn, print_fn) \
	static const struct ds_monitoring_operations name##_dm_ops = { \
		.get_index = get_idx_fn, \
		.get_name = get_name_fn, \
		.print_elem = print_fn, \
}

#define DS_MONITORING_INIT(xarray, _dm_ops) \
{ \
		.elements = &xarray, \
		.total_counts = 0, \
		.dm_ops = &_dm_ops, \
}

#define DECLARE_DS_MONITORING(name) \
	extern struct ds_monitoring name;

// 함수 선언
void find_ds_monitoring(struct ds_monitoring *dm, void *elem);
void insert_ds_monitoring(struct ds_monitoring *dm, unsigned long index, void *elem);
void print_ds_monitoring(struct ds_monitoring *dm);
void delete_ds_monitoring(struct ds_monitoring *dm);

// 추가 함수 선언
unsigned long get_thread_idx(void *elem);
const char *get_thread_name(void *elem);
void print_zone_dm(unsigned long pid, const char *name, unsigned long long count, int percentage);

//static long wb_check_background_flush(struct bdi_writeback *wb);
#endif
