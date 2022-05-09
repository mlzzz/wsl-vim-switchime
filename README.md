# wsl-vim-switchime

# 简介
- 在WSL中使用vim/neovim在退出插入模式时自动切换输入法  
# 使用方法
- 添加`美式键盘`
- 将 `switchIME.exe` 添加到 `PATH 环境变量` 
- 添加 `.vimrc`或`init.vim` 配置 
```
" 添加到.vimrc
if executable("fcitx") || executable("switchIME.exe")
  if executable("fcitx")
    let g:ime2en_cmd = "fcitx-remote -c"
    let g:ime2cn_cmd = "fcitx-remote -o"
  else
    let g:ime2en_cmd = "switchIME.exe en"
    let g:ime2cn_cmd = "switchIME.exe cn"
  endif

  " 设置输入法为英文模式
  function! IME2en()
    if executable("fcitx")
      let s:input_status = system("fcitx-remote")
    else
      let s:input_status = 2
    endif
    if s:input_status == 2
      let g:input_toggle = 1
      let l:a = system(g:ime2en_cmd)
    endif
  endfunction

  " 设置输入法为中文模式
    function! IME2zh()
    if exists("g:input_toggle") == 1
      if g:input_toggle == 1
        let l:a = system(g:ime2cn_cmd)
        let g:input_toggle = 0
      endif
    endif
  endfunction

  autocmd InsertLeave * call IME2en()
  autocmd InsertEnter * call IME2zh()
endif

```

# 测试通过
环境
- Windows11 + 微软五笔
