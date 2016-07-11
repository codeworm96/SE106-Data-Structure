charset="UTF-8"

# Usage
Note: Makefile has been modified, please use modified Makefile 
encoding: ./Compression fileA fileB
decoding: ./Compression -d fileB fileA
# 压缩文件格式定义

编码字符集包括文件中出现的各种字节 + 256(表示字节流末尾)

压缩文件分为两部分：header 和字节流。字节流即压缩后编码链接而成（最后以 eof_sign 的编码结尾）
而 header 通过储存前序遍历序列来储存 huffman tree ，每 9 bits 表示一个节点，内部节点以257(inner_sign)表示，而叶子节点即各个字符。