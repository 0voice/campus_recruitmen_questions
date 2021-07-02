Nginx的并发能力在同类型网页服务器中的表现，相对而言是比较好的，因此受到了很多企业的青睐，我国使用Nginx网站的知名用户包括腾讯、淘宝、百度、京东、新浪、网易等等。<br>
Nginx是网页服务器运维人员必备技能之一，下面为大家整理了一些比较常见的Nginx相关面试题，仅供参考：

# 1、请解释一下什么是Nginx?
Nginx是一个web服务器和方向代理服务器，用于HTTP、HTTPS、SMTP、POP3和IMAP协议。

# 2、请列举Nginx的一些特性。
Nginx服务器的特性包括：<br>
反向代理/L7负载均衡器<br>
嵌入式Perl解释器<br>
动态二进制升级<br>
可用于重新编写URL，具有非常好的PCRE支持<br>
# 3、请列举Nginx和Apache之间的不同点。
![不同点](https://imgconvert.csdnimg.cn/aHR0cDovLzViMDk4OGU1OTUyMjUuY2RuLnNvaHVjcy5jb20vaW1hZ2VzLzIwMTgxMDEwL2NkZTdiZjY5YTA5MTQxYmJiMDg1NDE2NjY1NTNkOTUyLmpwZw?x-oss-process=image/format,png)

# 4、请解释Nginx如何处理HTTP请求。
Nginx使用反应器模式。主事件循环等待操作系统发出准备事件的信号，这样数据就可以从套接字读取，在该实例中读取到缓冲区并进行处理。单个线程可以提供数万个并发连接。

# 5、在Nginx中，如何使用未定义的服务器名称来阻止处理请求?
只需将请求删除的服务器就可以定义为：
```
Server {
listen 80;
server_name “ “ ;
return 444;
}
```
这里，服务器名被保留为一个空字符串，它将在没有“主机”头字段的情况下匹配请求，而一个特殊的Nginx的非标准代码444被返回，从而终止连接。

# 6、 使用“反向代理服务器”的优点是什么?
反向代理服务器可以隐藏源服务器的存在和特征。它充当互联网云和web服务器之间的中间层。<br>
这对于安全方面来说是很好的，特别是当您使用web托管服务时。<br>

# 7、请列举Nginx服务器的最佳用途。
Nginx服务器的最佳用法是在网络上部署动态HTTP内容，使用SCGI、WSGI应用程序服务器、用于脚本的FastCGI处理程序。它还可以作为负载均衡器。

# 8、请解释Nginx服务器上的Master和Worker进程分别是什么?
Master进程：读取及评估配置和维持<br>
Worker进程：处理请求<br>

# 9、请解释你如何通过不同于80的端口开启Nginx?
为了通过一个不同的端口开启Nginx，你必须进入/etc/Nginx/sites-enabled/，如果这是默认文件，那么你必须打开名为“default”的文件。编辑文件，并放置在你想要的端口：
```
Like server { listen 81; }
```

# 10、请解释是否有可能将Nginx的错误替换为502错误、503?
502 =错误网关<br>
503 =服务器超载<br>
有可能，但是您可以确保fastcgi_intercept_errors被设置为ON，并使用错误页面指令。
```
Location / {
fastcgi_pass 127.0.01:9001;
fastcgi_intercept_errors on;
error_page 502 =503/error_page.html;
#…
}
```

# 11、在Nginx中，解释如何在URL中保留双斜线?
要在URL中保留双斜线，就必须使用merge_slashes_off;<br>
语法:merge_slashes [on/off]<br>
默认值: merge_slashes on<br>
环境: http，server<br>

# 12、请解释ngx_http_upstream_module的作用是什么?
ngx_http_upstream_module用于定义可通过fastcgi传递、proxy传递、uwsgi传递、memcached传递和scgi传递指令来引用的服务器组。

# 13、请解释什么是C10K问题?
C10K问题是指无法同时处理大量客户端(10,000)的网络套接字。

# 14、请陈述stub_status和sub_filter指令的作用是什么?
Stub_status指令：该指令用于了解Nginx当前状态的当前状态，如当前的活动连接，接受和处理当前读/写/等待连接的总数<br>
Sub_filter指令：它用于搜索和替换响应中的内容，并快速修复陈旧的数据

# 15、解释Nginx是否支持将请求压缩到上游?
您可以使用Nginx模块gunzip将请求压缩到上游。gunzip模块是一个过滤器，它可以对不支持“gzip”编码方法的客户机或服务器使用“内容编码:gzip”来解压缩响应。

# 16、解释如何在Nginx中获得当前的时间?
要获得Nginx的当前时间，必须使用SSI模块、$date_gmt和$date_local的变量。<br>
Proxy_set_header THE-TIME $date_gmt;

# 17、用Nginx服务器解释-s的目的是什么?
用于运行Nginx -s参数的可执行文件。

# 18、解释如何在Nginx服务器上添加模块?
在编译过程中，必须选择Nginx模块，因为Nginx不支持模块的运行时间选择。

# 19、什么是Nginx？
nginx是一个web服务器，反向代理服务器，缓存服务器

# 20、为什么使用nginx
跨平台，配置简单，非阻塞，高并发连接：处理2-3万并发连接数，官方监测能支持5万并发。<br>
内存消耗小：开启10个nginx才占150M内存，nginx处理静态资源好，消费内存少.<br>
内置的简单检查功能:如果一个服务器宕机,会做一个健康检查,再发送的请求就不会发送到宕机的服务器了,从新将请求提交给其他节点上.<br>
节省带宽：支持gzip压缩，可以添加浏览器本地缓存。<br>
稳定性高：宕机的概率非常小。<br>
接收用户请求是异步的：浏览器将请求发送给nginx服务器，他将用户请求全部接收下来，再一次性发送给后端的web服务器，极大减轻了web服务器的压力，一遍接收web服务器的返回数据，一边发送给浏览器客户端，网络依赖性比较低，只有ping通就可以负载均衡，可以用多台nginx服务器，使用dns做负载均衡，时间驱动，通信机制采用epoll模型。

# 21、为什么nginx性能这么高
得益于它的事件处理机制：异步非阻塞事件处理机制，运用了epoll模型，提供了一个队列，排队解决。

# 22、nginx的负载均衡算法都要哪些？
nginx的upstream目前支持4种方式的分配<br>
0）轮询：<br>
每次请求按时间顺序逐一分配到不同的后端服务器，如果后端服务器down掉，能自动剔除。<br>
1）weight 权重轮询<br>
指定轮询几率，weight和访问比例成正比，用于后端服务器性能不均的情况。<br>
2）ip_hash<br>
每次请求按访问ip的hash结果分配，这样每个访客固定访问一台后端服务器，可以解决session的问题。<br>
3）fair<br>
按后端服务器的响应来分配请求，响应时间短的优先分配。<br>
4）url_hash<br>
根据url的hash结果分配请求，是url定向到同一服务器，在upstream中加入hash语句后，server语句不能写入weight等其他参数，这种算法一般在后端缓存的时候比较适合。<br>
5）最少连接（least_conn）<br>
下一个请求被分派到活动连接数量最少的服务器

# 23、nginx的upstream中的ip_hash和url_hash的区别和特点。
ip_hash：每次请求访问，按照ip的hash结果分配，这样每个访客固定访问一台后端服务器，可以解决session的问题。<br>
url_hash: 根据url的hash结果分配请求，使url定向到同一服务器，在upstream中加入hash语句后，server语句中不能写入weight等其他参数，这种算法一般在后端缓存的时候比较适合。

# 24、什么是正向代理和反向代理
一个位于客户端与原始服务器之间的服务器，为了从原始服务器取得内容，客户端向代理发送了一个请求并指定目标（原始服务器），然后代理向原始服务器转交请求并将获得的内容返回给客户端，客户端才能使用正向代理。正向代理总结一句话就是：代理端代理的是客户端<br>
反向代理服务器作用在服务端，他在服务器端接收客户端的请求，然后将请求分发给具体的服务器进行处理，然后再将服务器的相应结果反馈给客户端，nginx就是一个反向代理服务器软件。

# 25、动态资源，静态资源分离？
动态资源，静态资源分离是让动态网站里的动态网页根据一定规则把不变的资源和经常变的资源区分开来，动静资源做好了拆分以后，我们就可以根据静态资源的特点将其做缓存操作，这就是网站静态化的核心思路，动态资源，静态资源分离简单概括是：动态文件和静态文件的分离。

# 26、为什么要做动静分离？
在我们的软件开发中，有些请求是需要后台处理的，有些请求不需要后台处理，这些不需要经过后台处理的文件称为静态文件，因此我们后台处理忽略静态文件。这会有人说那我后台忽略静态文件不就完了吗，当然这是可以的，但是这样后台的请求次数明显增多了，在我们对资源的响应速度有要求的时候，我们应该使用这种动静分离的策略去解决，动，静分离将网站静态资源与后台分开部署，提高用户访问静态代码的速度，降低对后台应用的访问，这里我们将静态资源放在nginx中，动态资源转发到tomcat服务器中。

# 27、生产中如何设置worker进程的数量呢？
在有多个cpu的情况下，可以设置多个worker，worker进程的数量可以设置到和cpu的核心数一样多，如果在单个cpu上起多个worker进程，那么操作系统会在多个worker之间进行调度，这种情况会降低系统性能，如果只有一个cpu，那么只启动一个worker进程就可以了。

# 28、Last-Modified,Expires,Max-age,Etag他们的含义，作用于浏览器端的是那些？作用于服务端的是那些？
Last-Modified：标记浏览器请求的URL对应的文件在服务器端最后被修改的时间。<br>
Expires：需要和last-Modified结合使用，用于控制请求文件的有效日期，当请求数据在有效期内时客户端从缓存请求数据而不是服务器端，当缓存中数据失效或过期，才决定从服务器更新数据。<br>
Max-age:指定的是文档被访问后的存活时间，这个时间是一个相对值（比如3600s）,相对的是文档第一次被请求时服务器记录的request_time（请求时间）<br>
Etag:服务器响应时，给url标记，并在http响应头中将其传送到客户端。<br>

# 29、为什么nginx不使用多线程？
Apache：创建多个进程和线程，而每个进程或线程都会为其分配cpu和内存（线程要比进程小的多,多以worker支持比perfork高的并发），并发多大会消耗光服务器资源。<br>
Nginx:采用单线程来异步非阻塞处理请求（管理员可以配置nginx主进程的工作进程数量）（epoll），不会为每个请求分配cpu和内存资源，节省了大量资源，同时也减少了大量的cpu的上下文切换。所以才使得nginx支持更高的并发。

# 30、nginx常见的优化配置有哪些？
### 安全优化：
隐藏nginx版本信息优化：修改nginx配置文件实现优化。<br>
server_tokens off;<br>
修改nginx进程用户信息：<br>
修改默认进程用户nginx为其他，如www.<br>
修改nginx服务上传文件限制：<br>
client_max_body_size 设置客户端请求报文主体最大尺寸，用户上传文件 大小。<br>
nginx图片及目录防盗链解决方法<br>
根据HTTP referer实现防盗链<br>
用户从哪里跳转过来的（通过域名）referer控制<br>
根据cookie防盗链<br>
nginx站点目录文件及目录权限优化<br>
只将用户上传数据目录设置为755用户和组使用nginx<br>
其余目录和文件为755/644，用户和组使用root<br>
使用普通用户启动nginx<br>
利用nginx -c参数启动nginx多实例，使master进程让普通用户管理。普通用户无法使用1-1024端口。使用iptables转发。<br>
控制nginx并发连接数<br>
控制客户端请求nginx的速率<br>
### 性能优化：
#### 1.调整worker_processes
指nginx要生成的worker数量，一般和cpu的核心数设置一致，高并发可以和cpu核心2倍.<br>
cat /proc/cpuinfo<br>
#### 2.优化nginx服务进程均匀分配到不同cpu进行处理。
利用worker_cpu_affinity进行优化让cpu的每颗核心平均。
#### 3.优化nginx事件处理模型
利用use epoll参数修改事件模型为epoll模型。<br>
事件模型指定配置参数放置在event区块中
#### 4.优化nginx单进程客户端连接数
利用worker_connections连接参数进行调整<br>
用户最大并发连接数=worker进程数*worker连接数
#### 5.优化nginx服务进程打开文件数
利用worker_rlimit_nofile 参数进行调整
#### 6.优化nginx服务数据高效传输模式。
利用sendfile on开启高速传输模式。<br>
tcp_nopush on 表示将数据积累到一定的量再进行传输。<br>
tcp_nopush on 表示将数据信息进行快速传输
#### 7.优化nginx服务超时信息。
keepalive_timeout 优化客户端访问 nginx服务端超时时间。<br>
http协议特点：连接断开后会给你保留一段时间

# 31、nginx常用模块
access 访问模块<br>
auth 认证模块<br>
gzip 压缩模块<br>
proxy 代理模块<br>
upstream 负载均衡<br>
rewrite 重写模块<br>
log 日志模块<br>
limit conn现在用户访问并发连接<br>
ssl模块<br>
autoindex 开启目录浏览

# 32、location匹配的优先级别
1.首先精准匹配 =<br>
2.其次前缀匹配 ^~<br>
3.其次是按文件中的顺序正则匹配<br>
4.然后配置不带任何修饰的前缀匹配<br>
5.最后交给/ 通用匹配<br>
6.当有匹配成功时，停止匹配，按当前匹配规则处理请求。
