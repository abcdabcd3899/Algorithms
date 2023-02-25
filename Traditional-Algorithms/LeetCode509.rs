impl Solution {
    // pub fn fib(n: i32) -> i32 {
    //     match n {
    //         0 => return 0,
    //         1 => return 1,
    //         _ => return Solution::fib(n-1) + Solution::fib(n-2)
    //     }
    // }
    // pub fn fib(n: i32) -> i32 {
    //     if n == 0 {
    //         return 0;
    //     }else if n == 1 {
    //         return 1;
    //     }else{
    //         return Solution::fib(n - 1) + Solution::fib(n - 2)
    //     }
    // }
    // pub fn fib(n: i32) -> i32 {
    //     if n == 0 {
    //         0
    //     }else if n == 1 {
    //         1
    //     }else{
    //         Solution::fib(n - 1) + Solution::fib(n - 2)
    //     }
    // }
     pub fn fib(n: i32) -> i32 {
        if n == 0 {
            return 0
        }else if n == 1 {
            return 1
        }else{
            return Solution::fib(n - 1) + Solution::fib(n - 2)
        }
    }
}
