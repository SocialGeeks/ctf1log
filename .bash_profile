mysql -h 10.195.177.109 -pXXSukJPX3k5b018QVpyy -u ctf_logger ctfdb -e "INSERT INTO ctfdb.HOST_ID VALUES ('${SSH_CLIENT%% *}',NOW());" &> /dev/null
function log2somewhere
{
  declare command
  command=$(fc -ln -0)
  echo "$USER:$command" | ctflog
}
trap log2somewhere DEBUG
readonly SSH_CLIENT
echo Hello. This is your key: ${SSH_CLIENT%% *}
. ~/.bashrc
