/**
 * @class       : hello
 * @author      : cromarmot (yexiaorain@gmail.com)
 * @created     : 星期四 3月 12, 2020 08:59:17 CST
 * @description : hello
 */

function HelloWorldPlugin(options) {
  // 使用 options 设置插件实例……
}

HelloWorldPlugin.prototype.apply = function(compiler) {
  compiler.plugin('done', function() {
    console.log('Hello World!');
  });
  // 设置回调来访问 compilation 对象：
  compiler.plugin("compilation", function(compilation) {
    // 现在，设置回调来访问 compilation 中的步骤：
    compilation.plugin("optimize", function() {
      console.log("Assets are being optimized.");
    });
  });
  compiler.plugin("emit", function(compilation, callback) {
    // 做一些异步处理……
    setTimeout(function() {
      console.log("Done with async work...");
      callback();
    }, 1000);
  });

  compiler.plugin('emit', function(compilation, callback) {
    // 在生成文件中，创建一个头部字符串：
    var filelist = 'In this build:\n\n';
    // 遍历所有编译过的资源文件，
    // 对于每个文件名称，都添加一行内容。
    for (var filename in compilation.assets) {
      filelist += ('- '+ filename +'\n');
    }

    // 将这个列表作为一个新的文件资源，插入到 webpack 构建中：
    compilation.assets['filelist.md'] = {
      source: function() {
        return filelist;
      },
      size: function() {
        return filelist.length;
      }
    };

    callback();
  });

  console.log('hooks: {{{')
  for(let k in compiler.hooks){
    console.log(k)
  }
  console.log('}}} hooks')

  compiler.hooks.compile.tap('MyPlugin', params => {
    console.log('以同步方式触及 compile 钩子。')
  })


  compiler.hooks.run.tapAsync('MyPlugin', (compiler, callback) => {
    console.log('以异步方式触及 run 钩子。')
    callback()
  })

  compiler.hooks.run.tapPromise('MyPlugin', compiler => {
    return new Promise(resolve => setTimeout(resolve, 1000)).then(() => {
      console.log('以具有延迟的异步方式触及 run 钩子')
    })
  })
};

module.exports = HelloWorldPlugin;
