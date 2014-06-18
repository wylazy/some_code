udf的演示
用于将Query Cache中的SQL提取出来，并打印在error日志中

此udf依赖mysql的源码，不可独立编译
将代码放到plugin/udf_qcdump目录下，编译成功以后，将udf_qcdump.so复制到mysql安装目录的lib/mysql/plugin目录下

在SQL终端中执行如下操作:
CREATE FUNCTION qcdump RETURNS STRING SONAME "udf_qcdump.so";
select qcdump(); #查看当前query cache的SQL
drop function qcdump;
