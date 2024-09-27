import yaml

def handle_r(r: dict):
    assert len(r) == 1 + 6
    print(r['desc'])
    r0 = int(r[0], 16)
    int_val  = (r0 & 0b1111111111111111 << 15) >> 15
    frac_val = (r0 & 0b111111111111 << 3) >> 3
    r1 = int(r[1], 16)
    mod_val  = (r1 & 0b111111111111 << 3) >> 3
    r2 = int(r[2], 16)
    d_val    = (r2 & 0b1 << 25) >> 25
    r_val    = (r2 & 0b1111111111 << 14) >> 14
    t_val    = (r2 & 0b1 << 24) >> 24
    r4 = int(r[4], 16)
    rfdiv_val = 2 ** ((r4 & 0b111 << 20) >> 20)
    print(f'INT={int_val}, FRAC={frac_val}, MOD={mod_val}, D={d_val}, R={r_val}, T={t_val}, RF_DIVIDER={rfdiv_val}')
    f_pfd = 25 * ((1 + d_val)/(r_val * (1. + t_val)))
    print(f'f_pfd={f_pfd:.2f}MHz')
    rf_out = (f_pfd * (int_val + (frac_val/mod_val))) / rfdiv_val
    print(f'RF_out={rf_out:.2f}MHz')

with open('adf4351-registers.yml', 'r') as f:
    reg_configs: list = yaml.safe_load(f)
    for _r in reg_configs:
        handle_r(_r)