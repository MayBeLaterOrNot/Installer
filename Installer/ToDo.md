- 提示杀死现有HikLink进程
	- 遍历进程树，挨个杀死HikLink进程，杀完之后再检查一遍，直到全部杀死
- 静默执行HikLink的卸载程序
	- 等待卸载进程退出，卸载完成后检查安装目录是否存在残留，存在的话，删除
- 
- 相关程序哈希值要通知运维人员
