set nu
set ts=2
set shiftwidth=2
set noswf
set nobackup
set expandtab
set autoread
set autoindent
set nocompatible               " be iMproved
filetype off                   " required!
set hlsearch
set backspace=2

set expandtab ts=2 sw=2 sts=2 tw=100
" set fenc=gb18030
set fenc=utf-8
set encoding=utf-8
set fileencodings=utf-8,chinese,ISO_8859,GBK,GB18030

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

hi DiffChange term=bold ctermbg=3 guibg=LightMagenta
hi DiffText   guibg=#ff0000 guifg=fg gui=bold term=reverse cterm=bold ctermbg=8

" let Vundle manage Vundle
" required!
Plugin 'gmarik/Vundle.vim'

" My Bundles here:
"
" original repos on github
Plugin 'tpope/vim-fugitive'

" vim-scripts repos
Plugin 'vim-scripts/L9'
Plugin 'vim-scripts/FuzzyFinder'
" Plugin 'vim-scripts/AutoComplPop'
Plugin 'vim-scripts/Auto-Pairs'
Plugin 'vim-scripts/The-NERD-tree'
Plugin 'vimcn/NERD_tree.vim.cnx'
Plugin 'vim-scripts/taglist.vim'
Plugin 'vim-scripts/google.vim'
Plugin 'mileszs/ack.vim'
Plugin 'nsf/gocode', {'rtp': 'vim/'}
Plugin 'fatih/vim-go'
Plugin 'Valloric/YouCompleteMe'
" Plugin 'Valloric/vim-valloric-colorscheme'
" Plugin 'flazz/vim-colorschemes'
" Plugin 'endel/vim-github-colorscheme'

" Other repos

call vundle#end()            " required
filetype plugin indent on    " required
syntax on
" colorscheme default
" set background=dark
colorscheme valloric

nmap <silent> `ff :FufFile<CR>
nmap <F2> :YcmCompleter FixIt<CR>
nmap <F3> :YcmCompleter GoToDefinitionElseDeclaration<CR>

nmap <F4> :bp<CR>
nmap <F5> :bn<CR>

nmap <F6> :cp<CR>
nmap <F7> :cn<CR>

nmap <F8> :make %:r<CR>
nmap <F9> :! ./%:r<CR>

" :nmap <C-Right> <C-W>l
" :nmap <C-Left> <C-W>h
" :nmap <C-Up> <C-w>k
" :nmap <C-Down> <C-w>j
:nmap <S-Left> :tabprev<CR>
:nmap <S-Right> :tabnext<CR>

let g:fuf_abbrevMap = {
                \   "webhdfs:" : [
                                \     "infra/webhdfs/**/",
                \     "assets/lib/**/",
                \   ],
                \   "css:" : [
                                \     "assets/css/**/"
                \   ],
                \   "view:" : [
                                \     "application/views/**/"
                \   ],
                \   "common:" : [
                                \     "~/workspace/opensource/envoy/source/common"
                \   ],
                \   "server:" : [
                                \     "~/workspace/opensource/envoy/source/server"
                \   ],
                \   "redis:" : [
                                \     "~/workspace/opensource/envoy/source/extensions/filters/network/redis_proxy"
                \   ],
                \ }

function InsertPythonHeader()
  let l1 = getline(1)
  let l2 = getline(2)
  if  match('\#!/', l1) == 0
    exec 1
    normal O
    call setline(1,'#!/usr/bin/env python')
  endif
  if match("\#", l2) == 0 && (match("-", l2)  != 2 || (match("code", l2) != 2))
    exec 2
    normal O
    call setline(2,'#-*- coding:utf-8 -*-')
  endif
endfunction

au FileType python call InsertPythonHeader()

let g:go_fmt_autosave = 0
let g:go_highlight_trailing_whitespace_error = 0
let g:ycm_global_ycm_extra_conf = '~/.vim/.ycm_extra_conf.py'
let g:ycm_autoclose_preview_window_after_insertion = 1
let g:ycm_autoclose_preview_window_after_completion = 1

packadd termdebug
let g:termdebug_wide = 80

highlight YcmErrorSection ctermfg=255 ctermbg=162

