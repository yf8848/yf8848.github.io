---
layout:     post
title:      Vim 配置
subtitle:   vim config for go
date:       2019-03-22
author:     abra
header-img: 
catalog: true
tags:
    - vim
    - 开发工具
---

### vim conf for go 

​	以下配置可见 git 仓库(https://github.com/yf8848/gitconf.git)，可直接 clone 下来，放在本地目录用，有个别插件需要手动执行一些命令，下面列出。

#### 基本配置

​	首先声明，有些 Linux 发行版本不支持全功能的 vim，需要从源码重新安装。

​	**.vimrc **文件可以配置 vim 的基本功能；个人具体配置如下：

```sh
set nocompatible            " 关闭 vi 兼容模式
syntax on                   " 自动语法高亮
colorscheme molokai         " 设定配色方案
set number                  " 显示行号
set cursorline              " 突出显示当前行
set ruler                   " 打开状态栏标尺
set shiftwidth=4            " 设定 << 和 >> 命令移动时的宽度为 4
set softtabstop=4           " 使得按退格键时可以一次删掉 4 个空格
set tabstop=4               " 设定 tab 长度为 4
set nobackup                " 覆盖文件时不备份
set autochdir               " 自动切换当前目录为当前文件所在的目录
filetype plugin indent on   " 开启插件
set backupcopy=yes          " 设置备份时的行为为覆盖
set ignorecase smartcase    " 搜索时忽略大小写，但在有一个或以上大写字母时仍保持对大小写敏感
set nowrapscan              " 禁止在搜索到文件两端时重新搜索
set incsearch               " 输入搜索内容时就显示搜索结果
set hlsearch                " 搜索时高亮显示被找到的文本
set noerrorbells            " 关闭错误信息响铃
set novisualbell            " 关闭使用可视响铃代替呼叫
set t_vb=                   " 置空错误铃声的终端代码

" set showmatch               " 插入括号时，短暂地跳转到匹配的对应括号
" set matchtime=2             " 短暂跳转到匹配括号的时间

set magic                   " 设置魔术
set hidden                  " 允许在有未保存的修改时切换缓冲区，此时的修改由 vim 负责保存
set guioptions-=T           " 隐藏工具栏
set guioptions-=m           " 隐藏菜单栏
set smartindent             " 开启新行时使用智能自动缩进
set backspace=indent,eol,start      " 不设定在插入状态无法用退格键和 Delete 键删除回车符
set cmdheight=1             " 设定命令行的行数为 1
set laststatus=2            " 显示状态栏 (默认值为 1, 无法显示状态栏)
set statusline=\ %<%F[%1*%M%*%n%R%H]%=\ %y\ %0(%{&fileformat}\ %{&encoding}\ %c:%l/%L%)\    " 设置在状态行显示的信息
set foldenable              " 开始折叠
set foldmethod=syntax       " 设置语法折叠
set foldcolumn=0            " 设置折叠区域的宽度
setlocal foldlevel=1        " 设置折叠层数为
" set foldclose=all           " 设置为自动关闭折叠
```





#### 插件安装

######  **Vim-plug**

由于用到了一些插件，本文所用的插件管理包是 **Vim-plug**。安装方式如下：

- unix

  ```sh
  curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
      https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
  ```

- Neovim

  ```sh
  curl -fLo ~/.local/share/nvim/site/autoload/plug.vim --create-dirs \
      https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
  ```

- **配置**

  编辑**.vimrc**(Neovim是~/.config/nvim/init.vim)
  添加vim-plug配置，以call plug#begin()开头，call plug#end()结尾，中间是插件列表，begin可以接受参数指定存放插件的位置(中间的插件也是个人安装的)：

  ```sh
  " Specify a directory for plugins (for Neovim: ~/.local/share/nvim/plugged)
  call plug#begin('~/.vim/plugged')
  
  " Any valid git URL is allowed
  Plug 'https://github.com/junegunn/vim-github-dashboard.git'
  
  " NERD Tree
  Plug 'scrooloose/nerdtree'
  " NERD Tree tab支持
  Plug 'jistr/vim-nerdtree-tabs'
  " NERD Tree git支持
  Plug 'Xuyuanp/nerdtree-git-plugin'
  
  " Vim-Go 插件
  "Plug 'fatih/vim-go', { 'tag': '*' }
  Plug 'fatih/vim-go', { 'do': ':GoUpdateBinaries' }
  
  " 自动补全
  Plug 'https://github.com/Valloric/YouCompleteMe.git'
  
  " taglist
  Plug 'https://github.com/vim-scripts/taglist.vim.git'
  
  " Moloka theme
  Plug 'https://github.com/tomasr/molokai.git'
  
  " tagbar
  Plug 'https://github.com/majutsushi/tagbar.git'
  
  " ctrlp.vim
  Plug 'https://github.com/kien/ctrlp.vim.git'
  
  " Initialize plugin system
  call plug#end()
  ```

###### 插件安装

完成上面的动作，已经配置好插件管理理包和需要安装的插件；下面就可以安装插件了。之前先简单说一下 vim-plug的使用。

- 配置插件：

  ```sh
  " Plug + 插件http(s)链接
  Plug 'https://github.com/majutsushi/tagbar.git'
  ```

- 配置文件生效

  ``` sh
  source ~/.vimrc
  ```

- 安装 vim 插件

  ``` sh
  vim .				//进入 vim
  :PlugInstall	//安装配置的插件(获取远端 git 仓库)
  ```

  

### vim-go

链接：https://github.com/fatih/vim-go

- **.vimrc**:

  ```vb
  " Vim-Go 插件
  Plug 'fatih/vim-go', { 'do': ':GoUpdateBinaries' }
  ```

- vim命令行模式安装 vim-go依赖

  ```sh
  :GoInstallBinaries
  ```



#### tagbar+gotags 

- 安装，配置

  ```sh
  go get -u github.com/jstemmer/gotags
  ```

  - **~/.vimrc:**

    ```go
    " tagbar
    Plug 'https://github.com/majutsushi/tagbar.git'
    
    "-----------------------------------------------------------------=
    " plugin - tagbar.vim   显示文件结构
    "-----------------------------------------------------------------
    nmap <F8> :TagbarToggle<CR>
    
    let g:tagbar_type_go = {
        \ 'ctagstype' : 'go',
        \ 'kinds'     : [
            \ 'p:package',
            \ 'i:imports:1',
            \ 'c:constants',
            \ 'v:variables',
            \ 't:types',
            \ 'n:interfaces',
            \ 'w:fields',
            \ 'e:embedded',
            \ 'm:methods',
            \ 'r:constructor',
            \ 'f:functions'
        \ ],
        \ 'sro' : '.',
        \ 'kind2scope' : {
            \ 't' : 'ctype',
            \ 'n' : 'ntype'
        \ },
        \ 'scope2kind' : {
            \ 'ctype' : 't',
            \ 'ntype' : 'n'
        \ },
        \ 'ctagsbin'  : 'gotags',
        \ 'ctagsargs' : '-sort -silent'
    \ }
    
    ```

  - 可以通过Ctrl + ]跳至符号定义处，Ctrl + t返回。
  - F8 开启函数侧边栏；F3 开启目录树；ctrl+w(两次切换窗口)

#### 自动补全-YouCompleteMe

​	链接：https://github.com/Valloric/YouCompleteMe

- **.vimrc**

  ```go
  "YouCompleteMe 自动补全
  Plug 'https://github.com/Valloric/YouCompleteMe.git'
  ```

- 支持 go

  ```go
  cd ~/.vim/pluged/YouCompleteMe
  ./install.py --go-completer
  ```

#### 代码提示

- 安装 gocode

  ```sh
  go get -u github.com/nsf/gocode
  ```

  然后cd到gocode/vim下，执行./update.sh，实际就是把vim插件拷贝到~/.vim/下。然后编辑go文件，就会有代码提示.

#### **安装molokai theme**

- 下载

```sh
    mkdir ~/.vim/colors
    cd ~/.vim/colors
    git clone ://github.com /fatih/molokai/blob/master/colors/molokai.vim
```

- .vimrc添加一行：

  ```sh
  colorscheme molokai
  ```

  