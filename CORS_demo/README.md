# CORS

## Capture

```bash
tcpdump -i lo 'port 5000' -vv -x -X
```

## In browser console

```bash
fetch("http://127.0.0.1:5000").then(result=>console.log(result))
fetch("http://127.0.0.1:5000/xxx",{method: "POST",credentials:"include"}).then(result=>console.log(result))
```

## With curl

```bash
curl -X POST -H "Origin: https://www.baidu.com" http://127.0.0.1:5000/xxx
```

## With static html

```
<!DOCTYPE html>
<html>
  <header>
    <title></title>
  </header>
  <body>
    <div></div>
    <script>
      const xhr = new XMLHttpRequest();
      const url = 'http://127.0.0.1:5000/xxx';
      xhr.open('POST', url);
      xhr.send();
    </script>
  </body>
</html>
```

## Python with flask flask-cors

```bash
cd flask_demo
python3 -m venv venv
. venv/bin/active
pip install flask flask-cors
python3 app.py
```

## Nodejs express

```bash
cd express_demo
yarn
node app.js
```

## OutPut

```
IP (tos 0x0, ttl 64, id 30245, offset 0, flags [DF], proto TCP (6), length 72)
    localhost.5000 > localhost.45592: Flags [P.], cksum 0xfe3c (incorrect -> 0xdb33), seq 174:194, ack 537, win 512, options [nop,nop,TS val 3514469229 ecr 3514469229], length 20
	0x0000:  4500 0048 7625 4000 4006 c688 7f00 0001  E..Hv%@.@.......
	0x0010:  7f00 0001 1388 b218 a3e6 4bd5 50ac 8872  ..........K.P..r
	0x0020:  8018 0200 fe3c 0000 0101 080a d17a 8b6d  .....<.......z.m
	0x0030:  d17a 8b6d 3c70 3e48 656c 6c6f 2c20 576f  .z.m<p>Hello,.Wo
	0x0040:  726c 6421 3c2f 703e                      rld!</p>

IP (tos 0x0, ttl 64, id 10609, offset 0, flags [DF], proto TCP (6), length 58)
    localhost.5000 > localhost.33622: Flags [P.], cksum 0xfe2e (incorrect -> 0xa0e0), seq 173:179, ack 784, win 512, options [nop,nop,TS val 3515041534 ecr 3515041534], length 6
	0x0000:  4500 003a 2971 4000 4006 134b 7f00 0001  E..:)q@.@..K....
	0x0010:  7f00 0001 1388 8356 edfc 5eb6 696a eb5f  .......V..^.ij._
	0x0020:  8018 0200 fe2e 0000 0101 080a d183 46fe  ..............F.
	0x0030:  d183 46fe 7979 7979 7979                 ..F.yyyyyy
```

跨域依然被发送, 且服务器会执行和返回, 只是当不满足时, 加了credentials:"include"也不会带cookie, 浏览器也不展示结果
