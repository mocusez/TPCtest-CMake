#处理顺序：
```
FROM -> JOIN -> 
WHERE -> 
GROUP BY -> HAVING -> 
ORDER BY -> 
SELECT -> LIMIT / OFFSET

```
#DATE 比较
日期比较大小可以使用str大小比较！



FROM 子句
首先处理 FROM 子句，确定查询涉及哪些表。

JOIN
如果有 JOIN 操作，它会在 FROM 之后立即执行，用于结合 FROM 子句中指定的表。

WHERE 子句
然后是 WHERE 子句，它用于过滤 FROM 和 JOIN 生成的结果集，只留下符合条件的行。

GROUP BY 子句
接着执行 GROUP BY 子句，将结果集中的行分组，以便于后续的聚合操作。

HAVING 子句
HAVING 子句用于过滤 GROUP BY 后的分组结果，只保留满足条件的分组。

SELECT 子句
SELECT 子句之后执行，它用于选择从上述步骤生成的表中的特定列。

ORDER BY 子句
最后执行 ORDER BY 子句，根据指定的列对最终的结果集进行排序。

LIMIT / OFFSET 子句
如果有 LIMIT 或 OFFSET 子句，它们会在所有其他操作完成后执行，用于限制返回的结果数量或跳过一定数量的行。