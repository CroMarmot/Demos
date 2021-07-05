import { add } from "./util.js"

describe("测试算数运算",()=>{
    it("测试加法运算",()=>{
        const add5 = add(5)
        expect(add5(5)).toBe(10)
    })
})
