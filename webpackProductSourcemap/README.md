# 🚀 Welcome to your new awesome project!

`npx webpack init webpackProductSourcemap --force --template=default`

This project has been created using **webpack-cli**, you can now run

```
npm run build
```

or

```
yarn build
```

to bundle your application

# 方案

最直接`source-map`，会暴露给用户，虽然可以上面搞一层nginx来搞不过有点强行解决了

使用`hidden-source-map`,需要在chrome查看文件的页面右键 手动添加，缺点就是每次手动，且已经输出的不会变化，还要执行之前断点一下

最后就是https://webpack.docschina.org/plugins/source-map-dev-tool-plugin/ 配合自动化构建，把你的map部署到一个私有才能访问的路径上，这个是操作会更复杂，但是一旦搭建好了，比上面都更好的解决方案

