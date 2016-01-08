#!/bin/bash
#Author Abil N George<mail@abilng.in>

{ # this ensures the entire script is downloaded #

install_sublime(){
  sudo add-apt-repository ppa:webupd8team/sublime-text-2 &&
  sudo apt-get update &&
  sudo apt-get install sublime-text
}

install_atom(){
  wget https://github.com/atom/atom/releases/download/v1.3.2/atom-amd64.deb &&
  sudo dpkg --install atom-amd64.deb
}

install_softwares() {
   sudo apt-get update && sudo apt-get install $@
}

install_nodeJs() {
  if [[ -z "$1" ]]; then
    echo "ERROR: Version is Not Specified"
    return 1;
  fi

  echo "Installing NVM"
  curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.30.1/install.sh | bash
  source ~/.nvm/nvm.sh
  nvm install $1
  echo "[[ -r $NVM_DIR/bash_completion ]] && . $NVM_DIR/bash_completion" >>~/.bashrc
  echo "nvm use $1" >>~/.bashrc
  [[ ! -z "$2" ]] && npm config set registry $2
}

PROGRAMS="git wget vim emacs g++ curl wget"
NODE_VERSION="v0.10.32"
NPM_REPO="http://registry.npmjs.org/"

install_softwares $PROGRAMS &&
install_nodeJs $NODE_VERSION $NPM_REPO &&
install_sublime &&
install_atom

}
