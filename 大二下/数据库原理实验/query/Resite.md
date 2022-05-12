# SQL 易错总结

## 聚集函数

1. `COUNT(*) `跳过空值
2. 聚集函数只作用于`SELECT`子句和`GROUP BY`中的`HAVING`子句



## 子查询

### 相关与不相关

* **相关：** 子查询中带有父查询列名

* **不相关：** 无父查询属性



### 嵌套查询分类

* IN
* ALL / ANY
* EXISTS / NO EXISTS



## 空值

### 判断是否为空值

```sql
is NULL
is NOT NULL
```

