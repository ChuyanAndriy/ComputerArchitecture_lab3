
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_AUTHOR("Andriy Chuyan <majyr295@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint parameter = 1;
module_param(parameter, uint, 0444);
MODULE_PARM_DESC(parameter, "hello parameter");

struct my_data {
	ktime_t time;
	struct list_head list; 
};

static LIST_HEAD(my_list);

static int __init hello_init(void)
{
	if (parameter == 0 || (parameter >= 5 && parameter <= 10))
	{
		printk(KERN_WARNING "Parameter is 0 or ranges from 5 to 10!\n");
	}
	else if (parameter > 10)
	{
		printk(KERN_ERR "ERROR: Parameter is greater than 10!\n");
		return -EINVAL;
	}
	
	struct my_data *tmp;
	int i;
	for (i = 0; i < parameter; i++)
	{
		tmp = kmalloc(sizeof(struct my_data), GFP_KERNEL);
		tmp->time = ktime_get();
		list_add_tail(&tmp->list, &my_list);
		
		printk(KERN_EMERG "Hello, world!\n");
	}
	return 0;
}

static void __exit hello_exit(void)
{
	struct my_data *tmp, *next;
	list_for_each_entry_safe(tmp, next, &my_list, list)
	{
		printk(KERN_EMERG "ktime = %lld\n", ktime_to_ns(tmp->time));
		list_del(&tmp->list);
		kfree(tmp);
	}
}

module_init(hello_init);
module_exit(hello_exit);
