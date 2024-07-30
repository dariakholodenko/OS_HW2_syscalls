#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage long sys_hello(void) {
    printk("Hello, World!\n");
    return 0;
}
asmlinkage long sys_set_weight(int weight) {
    if (weight < 0){
        return -EINVAL;
    }
    current->my_weight = weight;
    return 0;
}
asmlinkage long sys_get_weight(void) {
    return current->my_weight;
}
void get_leaf_children(int* sum, struct task_struct * cur){
    struct task_struct * temp;
    struct list_head * temp_list, *children_tasks;
    children_tasks = &cur->children;
    if (list_empty(children_tasks) == 0)
    {
        list_for_each(temp_list, &cur->children){
            temp = list_entry(temp_list, struct task_struct, sibling);
            get_leaf_children(sum, temp);
        }
        return;
    }else{
        *sum += cur->my_weight;
        return;
    }   
}
asmlinkage long sys_get_leaf_children_sum(void) {
    struct list_head* children_tasks = &current->children;
    int sum = 0;
    if (list_empty(children_tasks)){
        return -ECHILD;
    }
    get_leaf_children(&sum, current);
    return sum;
}
asmlinkage long sys_get_heaviest_ancestor(void) {
    struct task_struct* temp = current->real_parent;
    int temp_max_weight = current->my_weight;
    int heaviest_pid = current->pid;
    while (temp != temp->parent)
    {
        if (temp->my_weight >= temp_max_weight)
        {
            temp_max_weight = temp->my_weight;
            heaviest_pid = temp->pid;
        }
        temp = temp->parent;
    }
    return heaviest_pid;
}
