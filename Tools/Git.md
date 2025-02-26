


[十分钟学会正确的github工作流，和开源作者们使用同一套流程_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV19e4y1q7JJ/?spm_id_from=333.999.0.0&vd_source=eac5ac1806a34c555049154a3c3a656e)


1. `git fetch origin` 到 local
2. 创建 myfeature 新分支，并切换 `git checkout -b my-feature`
3. 进行修改，`git diff` 查看改变， `git add <file>` 加入暂存区，`git commit` 本地更新
4. `git push origin my-feature` 到 remote 
5. `git fetch origin` 到 local，在 `my-feature` 分支 `git rebase main` 合并
6. `git push origin my-feature` 到 remote 
7. 提个PR，删除 local 和 remote 的 my-feature 分支



实际开发项目可能还会更复杂，使用到的分支比视频里更多 
main：生产环境，也就是你们在网上可以下载到的版本，是经过了很多轮测试得到的稳定版本。 release： 开发内部发版，也就是测试环境。 
dev：所有的feature都要从dev上checkout。 feature：每个需求新创建的分支。
下面介绍一下一个新需求过来的git操作流程： 
1. 从dev分支上checkout -b new-feature，进行开发 
2. 开发完后，经过自测没问题了，准备发版 
3. merge到release分支上进行发版，并打tag 
4. 有bug就直接在release上进行修改，改完再次发版，打tag，直到测试人员验证完毕 
5. 这时可以将release分支合并到dev上，也可以删除掉feature分支了，并等待通知是否将此功能上线（发布正式版本，也就是在正式服务器上运行），如果上线，那就merge到main（master）分支，当然了有可能需要将ip改为生产服务器的地址，并打上一个official tag。 
6. 如果上线后，发现有bug，如果此时main分支已经又合并上新功能B了，但是这个临时的版本又不想包含B的功能，那么可以切换到上次的official tag，checkout -b一个hotfix分支进行bug修复，hotfix分支要进行保留，不能删除。测试没问题就可以发版了，最后可以合并到main上。 
一般的项目这套流程应该就足够了。所有的发版tag都会集中到release，main，hotfix分支上，所有的需求都会从dev上拉取，这样能保证代码是完整可用的，是经过每次release合并过来的


---