# 动态规划问题

## 特征
每次决策依赖于当前状态，又随即引起状态的转移。一个决策的序列就是在变化的状态中产生出来的；也叫作 __多阶段最优化决策解决问题的过程__

## 思路
1. 将问题分解成若干个子问题
2. 按顺序求解，前一阶段的解为后一子问题的求解提供了有用信息(非相互独立)
3. 在求解任一子问题，列出各种可能的解，通过决策保留最优局部解
4. 依次解决各子问题，最后一个问题就是初始问题的解

## 转换成数学语言

$\sum_{i=0}^N$
