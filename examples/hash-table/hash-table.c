/*************************************************************************
> FileName: hash-table.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: 2025年03月08日 星期六 14时35分53秒
 ************************************************************************/
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/hashtable.h>


struct MyItem
{
	int key;
	struct hlist_node node;
};

// 创建hash表，
// 第一个参数表示变量名
// 第二个参数表示实际桶数，实际桶数为2^(传入值)
// hash_add() 添加元素
// hash_del() 删除元素
// hash_for_each() 遍历元素
// hash_for_each_safe() 安全编译(允许删除)
DEFINE_HASHTABLE(hash1, 2);
spinlock_t hash1Lock;

static void add_item(int key)
{
	struct MyItem* item = kmalloc(sizeof(struct MyItem), GFP_KERNEL);
	item->key = key;

	// 添加到hash列表
	spin_lock(&hash1Lock);
	hash_add(hash1, &item->node, key);
	spin_unlock(&hash1Lock);
}

static void del_item(int key)
{
	struct hlist_node* tmp = NULL;
	struct MyItem* item = NULL;
	int bkt;

	spin_lock(&hash1Lock);
	hash_for_each_safe(hash1, bkt, tmp, item, node) {
		if (key == item->key) {
			hash_del(&item->node);
			kfree(item);
			item = NULL;
			break;
		}
	}
	spin_unlock(&hash1Lock);
}

static void print_all_items(void)
{
	struct MyItem* item = NULL;
	int bkt;

	spin_lock(&hash1Lock);
	hash_for_each(hash1, bkt, item, node) {
		printk("Key: %d\n", item->key);
	}
	spin_unlock(&hash1Lock);
}


static int __init hashtable_init(void)
{
	int i = 0; 

	spin_lock_init(&hash1Lock);

	for (; i < 1000; ++i) {
		add_item(i);
	}

	printk("hash table:\n");
	print_all_items();

	return 0;
}

static void __exit hashtable_exit(void)
{
	int i = 0;
	for (; i < 1000; ++i) {
		del_item(i);
	}
	printk("hash table is empty: %s\n", hash_empty(hash1) ? "true" : "false");
}

module_init(hashtable_init);
module_exit(hashtable_exit);
MODULE_LICENSE("GPL");
