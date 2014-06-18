udf的演示
定义一个聚集函数，用于计算结果集中每行数据里，为奇数的和

此udf不依赖mysql的源码，可独立编译，需要系统中已经安装了MySQL
可将代码放到任意目录下，编译成功以后，将udf_oddsum.so复制到mysql安装目录的lib/mysql/plugin目录下

在SQL终端中执行如下操作:
CREATE AGGREGATE FUNCTION oddsum RETURNS STRING SONAME "udf_oddsum.so";
select oddsum(val) from tb group by name; #查看当前query cache的SQL
drop function oddsum;
