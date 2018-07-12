# sort-algorithm
- 数据结构课设，八个排序算法的可视化(MFC实现)
- 主要代码写在`Class-DesignDlg.h`和`Class-DesignDlg.cpp`里

## 开发环境
- OS Name	Microsoft Windows 10 Enterprise N
- Total Physical Memory	15.9 GB
- Microsoft Visual Studio Community 2017

## 实现类容
- 八个排序算法的可视化过程（QUICK_SORT、BUBBLE_SORT、INSERT_SORT、HEAP_SORT、SELECTION_SORT、MERGE_SORT、SHELL_SORT、RADIX_SORT）参考[https://www.geeksforgeeks.org/sorting-algorithms/](https://www.geeksforgeeks.org/sorting-algorithms/)

## 不足

- 因为对每一次的显示是通过绘制一个大的白色画布覆盖所有类容再重新绘制矩形来实现的，所以当每一步间隔时间缩短（即sleep时间减少）时，会造成界面假死情况的发生。

## 演示
<img src="http://www.potatochip.cn/datastructer_sort_visualization.gif" width="80%">
