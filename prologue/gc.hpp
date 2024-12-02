int gc() {
    static char buf[1 << 16];
    static int bc, be;
    if (bc >= be)
        buf[bc = 0] = EOF, be = fread(buf, 1, sizeof(buf), stdin);
    return buf[bc++];
}
