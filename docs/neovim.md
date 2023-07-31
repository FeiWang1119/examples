
# install

## neovim

```sh
curl -LO https://github.com/neovim/neovim/releases/latest/download/nvim.appimage
chmod u+x nvim.appimage
./nvim.appimage

sudo mv ./nvim.appimage /usr/local/bin/nvim
```

## lazygit

```sh
LAZYGIT_VERSION=$(curl -s "https://api.github.com/repos/jesseduffield/lazygit/releases/latest" | grep -Po '"tag_name": "v\K[^"]*')
curl -Lo lazygit.tar.gz "https://github.com/jesseduffield/lazygit/releases/latest/download/lazygit_${LAZYGIT_VERSION}_Linux_x86_64.tar.gz"
tar xf lazygit.tar.gz lazygit
sudo install lazygit /usr/local/bin
```

## LazyVim

```sh
git clone https://github.com/LazyVim/starter ~/.config/nvim
```

## dependencies

apt install ripgrep // telescope grep doesn't work

apt install npm // markdown-preview  
cd ~/.local/share/nvim/lazy/markdown-preview.nvim/app && npm install

apt install xclip //previde a clipboard tool like xclip for using system's clipboard. 

