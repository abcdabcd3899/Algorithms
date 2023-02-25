-- 扩展性非常强的方法，逻辑很简单
--  Write your MySQL query statement below
select S1.Score, count(S2.Score) as 'Rank'
FROM Scores as S1,
(SELECT DISTINCT Score FROM Scores) S2
WHERE S1.Score<=S2.Score
GROUP BY S1.Id 
ORDER BY S1.Score DESC;


-- 使用窗口函数
select S.Score, S.row_num as 'Rank'
from
(
    select Score, dense_rank() over(order by Score desc) as row_num
    from Scores
)as S



-- 声明变量
select R.Score, R.row_num as 'Rank'   -- row_num的输出为varchar类型，导致这段代码不能AC
from
(
select Score, @tmp := case when @preScore = Score then @tmp else @tmp + 1 end as row_num,
       @preScore := Score
from 
    (select @tmp := 0) as t,
    (select @preScore := -1) as p,
    (select Id, Score from Scores order by Score desc) as s
) as R


-- 声明变量
select R.Score, R.row_num + 0 as 'Rank'  -- 注意：该段代码和上面代码的差别是: R.row_num + 0，这里将varchar转成int类型，这是因为题目的输出结果要求为int
from
(
select Score, 
       @tmp := case when @preScore <> Score then @tmp+1 else @tmp end as row_num,
       @preScore := Score
from 
    (select @tmp := 0) as t,
    (select @preScore := -1) as p,
    (select Id, Score from Scores order by Score desc) as s
) as R


-- MySQL中的强制类型，将varchar类型转换为一个signed（有符号整型）
select R.Score, convert(row_num, signed) as 'Rank'
from
(
select Score, @tmp := case when @preScore = Score then @tmp else @tmp + 1 end as row_num,
       @preScore := Score
from 
    (select @tmp := 0) as t,
    (select @preScore := -1) as p,
    (select Id, Score from Scores order by Score desc) as s
) as R

-- MySQL中的强制类型，将varchar类型转换为一个signed（有符号整型）
select R.Score,cast(row_num  as signed) as 'Rank'
from
(
select Score, @tmp := case when @preScore = Score then @tmp else @tmp + 1 end as row_num,
       @preScore := Score
from 
    (select @tmp := 0) as t,
    (select @preScore := -1) as p,
    (select Id, Score from Scores order by Score desc) as s
) as R


/*
在MySQL中将一个字符串转换为整型时有三种方法
(1) row_num + 0，即直接在需要转换的字段后面加0
(2) cast(需要转换的字段 as 转换后的类型)
(3)convert(需要转换的字段, 转换后的类型)
在MySQL中可以转换为下列类型
BINARY[(N)]  
CHAR[(N)]  
DATE  
DATETIME  
DECIMAL  
SIGNED   [INTEGER]  
TIME  
UNSIGNED   [INTEGER]
*/