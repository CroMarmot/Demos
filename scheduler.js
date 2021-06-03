class Scheduler {
  runningCnt = 0;
  waitingFn = [];

  async runTask() {
    if(this.runningCnt < 2 && this.waitingFn.length > 0){
      const fn = this.waitingFn[0].fn;
      const cb = this.waitingFn[0].cb;
      this.waitingFn.shift();
      this.runningCnt += 1;
      await fn().then(cb);
      this.runningCnt -= 1;
      this.runTask();
    }
  }

  async add(promiseFunc) {
    const res$ = new Promise(resolve => {
      this.waitingFn.push({
        fn:promiseFunc,
        cb:resolve,
      });
    })
    this.runTask();
    return res$
  }
}


const scheduler = new Scheduler();
const timeout = (time) => {
  return new Promise(r => setTimeout(r,time));
}

const addTask = (time, order) => {
  scheduler.add(() => timeout(time))
    .then(() => console.log(order))
}

addTask(1000,1)
addTask(500,2)
addTask(300,3)
addTask(400,4)

// log: 2 3 1 4
