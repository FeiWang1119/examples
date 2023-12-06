# If you come from bash you might have to change your $PATH.
# export PATH=$HOME/bin:/usr/local/bin:$PATH

# Path to your oh-my-zsh installation.
export ZSH=$HOME/.oh-my-zsh

# Set name of the theme to load --- if set to "random", it will
# load a random theme each time oh-my-zsh is loaded, in which case,
# to know which specific one was loaded, run: echo $RANDOM_THEME
# See https://github.com/ohmyzsh/ohmyzsh/wiki/Themes
ZSH_THEME="amuse"

# Set list of themes to pick from when loading at random
# Setting this variable when ZSH_THEME=random will cause zsh to load
# a theme from this variable instead of looking in $ZSH/themes/
# If set to an empty array, this variable will have no effect.
# ZSH_THEME_RANDOM_CANDIDATES=( "robbyrussell" "agnoster" )

# Uncomment the following line to use case-sensitive completion.
# CASE_SENSITIVE="true"

# Uncomment the following line to use hyphen-insensitive completion.
# Case-sensitive completion must be off. _ and - will be interchangeable.
# HYPHEN_INSENSITIVE="true"

# Uncomment one of the following lines to change the auto-update behavior
# zstyle ':omz:update' mode disabled  # disable automatic updates
# zstyle ':omz:update' mode auto      # update automatically without asking
# zstyle ':omz:update' mode reminder  # just remind me to update when it's time

# Uncomment the following line to change how often to auto-update (in days).
# zstyle ':omz:update' frequency 13

# Uncomment the following line if pasting URLs and other text is messed up.
# DISABLE_MAGIC_FUNCTIONS="true"

# Uncomment the following line to disable colors in ls.
# DISABLE_LS_COLORS="true"

# Uncomment the following line to disable auto-setting terminal title.
# DISABLE_AUTO_TITLE="true"

# Uncomment the following line to enable command auto-correction.
# ENABLE_CORRECTION="true"

# Uncomment the following line to display red dots whilst waiting for completion.
# You can also set it to another string to have that shown instead of the default red dots.
# e.g. COMPLETION_WAITING_DOTS="%F{yellow}waiting...%f"
# Caution: this setting can cause issues with multiline prompts in zsh < 5.7.1 (see #5765)
# COMPLETION_WAITING_DOTS="true"

# Uncomment the following line if you want to disable marking untracked files
# under VCS as dirty. This makes repository status check for large repositories
# much, much faster.
# DISABLE_UNTRACKED_FILES_DIRTY="true"

# Uncomment the following line if you want to change the command execution time
# stamp shown in the history command output.
# You can set one of the optional three formats:
# "mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# or set a custom format using the strftime function format specifications,
# see 'man strftime' for details.
# HIST_STAMPS="mm/dd/yyyy"

# Would you like to use another custom folder than $ZSH/custom?
# ZSH_CUSTOM=/path/to/new-custom-folder

# Which plugins would you like to load?
# Standard plugins can be found in $ZSH/plugins/
# Custom plugins may be added to $ZSH_CUSTOM/plugins/
# Example format: plugins=(rails git textmate ruby lighthouse)
# Add wisely, as too many plugins slow down shell startup.
plugins=(git zsh-autosuggestions zsh-syntax-highlighting)

source $ZSH/oh-my-zsh.sh

# User configuration

# export MANPATH="/usr/local/man:$MANPATH"

# You may need to manually set your language environment
# export LANG=en_US.UTF-8

# Preferred editor for local and remote sessions
# if [[ -n $SSH_CONNECTION ]]; then
#   export EDITOR='vim'
# else
#   export EDITOR='mvim'
# fi

# Compilation flags
# export ARCHFLAGS="-arch x86_64"

# Set personal aliases, overriding those provided by oh-my-zsh libs,
# plugins, and themes. Aliases can be placed here, though oh-my-zsh
# users are encouraged to define aliases within the ZSH_CUSTOM folder.
# For a full list of active aliases, run `alias`.
#
# Example aliases
# alias zshconfig="mate ~/.zshrc"
# alias ohmyzsh="mate ~/.oh-my-zsh"
alias .zshrc="vim ~/.zshrc"
alias dfm="dde-file-manager ./"
alias l="ls"
alias ll="ls -la"
alias ..="cd .."
alias n="nvim ."
alias rb="rm build -rf"
alias mb="mkdir build && cd build"
alias c="cmake -GNinja -Bbuild -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug"
alias b="cmake --build build | grep '\(error:\|failed\|undefine\)'"
alias i="sudo apt install"
alias u="sudo apt update"
alias s="apt-file search"
alias p="dpkg-buildpackage -us -uc -nc"
alias po="apt policy"
alias lg="lazygit"
alias doc="cd /home/fei/document"
alias repo="cd /home/fei/repo"
alias build="cd /home/fei/build"
alias example="cd /home/fei/repo/example"
alias common="cd /home/fei/repo/dtkcommon"
alias core="cd /home/fei/repo/dtkcore"
alias gui="cd /home/fei/repo/dtkgui"
alias widget="cd /home/fei/repo/dtkwidget"
alias das="cd /home/fei/repo/dde-app-services"
alias dtkdeclarative="cd /home/fei/repo/dtkdeclarative"
alias integration="cd /home/fei/repo/qt5integration"
alias platform-plugins="cd /home/fei/repo/qt5platform-plugins"
alias dcc="cd /home/fei/repo/dde-control-center"
alias dss="cd /home/fei/repo/dde-session-shell"
alias dl="cd /home/fei/repo/dde-launcher"
alias dock="cd /home/fei/repo/dde-dock"
alias dla="cd /home/fei/repo/dde-launchpad"
alias dam="cd /home/fei/repo/dde-application-manager"
alias dsc="cd /home/fei/repo/deepin-signtool-client"
alias dfp="cd /home/fei/repo/deepin-fcitx5configtool-plugin"
alias di="cd /home/fei/repo/deepin-im"
alias dw="cd /home/fei/repo/dde-widgets"
alias dk="cd /home/fei/repo/deepin-kwin"
alias da="cd /home/fei/repo/dde-appearance"
alias sd="cd /home/fei/repo/startdde"
alias ds="cd /home/fei/repo/dde-session"
alias dsl="cd /home/fei/repo/dde-shell"
alias dsu="cd /home/fei/repo/dde-session-ui"
alias jd="cd /home/fei/repo/job-data"
alias qtbase5="cd /home/fei/repo/qtbase-opensource-src-5.11.3.40"
alias qtbase="cd /home/fei/repo/qtbase"
alias qtdeclarative="cd /home/fei/repo/qtdeclarative"
alias qttools="cd /home/fei/repo/qttools"
alias qtwayland="cd /home/fei/repo/qtwayland"
alias diff="/home/fei/software/p4v/bin/p4merge"
alias qt5-plugin="cd /usr/lib/x86_64-linux-gnu/qt5/plugins"
alias qt6-plugin="cd /usr/lib/x86_64-linux-gnu/qt6/plugins"
alias qtcreator-plugin="cd /usr/lib/x86_64-linux-gnu/qtcreator/plugins"
alias cmake-config="cd /usr/lib/x86_64-linux-gnu/cmake"
alias lowercase="for i in *; do mv "$i" "$(echo $i|tr A-Z a-z)"; done"
export GOPATH=/usr/share/gocode:/home/fei/go
DEBEMAIL="wangfeia@uniontech.com"
DEBFULLNAME="wangfei"
export DEBEMAIL DEBFULLNAME
