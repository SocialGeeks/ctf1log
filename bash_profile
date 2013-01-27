mysql -h 10.195.177.109 -pXXSukJPX3k5b018QVpyy -u ctf_logger ctfdb -e "INSERT INTO ctfdb.HOST_ID VALUES ('${SSH_CLIENT%% *}',NOW());" &> /dev/null
function log2somewhere
{
  declare command
  command=$(fc -ln -0)
  logger -p local1.notice -t bash -i "$USER:$SSH_CLIENT:$SSH_CONNECTION:$command"
  echo "$USER:$command" | ctflog
}
trap log2somewhere DEBUG
echo Hello. This is your key: ${SSH_CLIENT%% *}
. ~/.bashrc
