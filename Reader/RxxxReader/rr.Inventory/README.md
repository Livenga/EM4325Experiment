# rr.Inventory
Impinj 社製リーダライタに対して Inventory 命令を発行します.  
EM4325 を検出した場合, EPC 領域末尾 32bit を気圧センサのデータとして認識します.

## Usage
```sh
$ dotnet run --project rr.Inventory.csproj \
    -- [リーダ名, ホスト名]
```
