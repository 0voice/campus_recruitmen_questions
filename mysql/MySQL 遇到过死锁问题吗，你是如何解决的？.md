# 参考答案
我排查死锁的一般步骤是酱紫的：
*	查看死锁日志show engine innodb status;
*	找出死锁Sql
*	分析sql加锁情况
*	模拟死锁案发
*	分析死锁日志
*	分析死锁结果
