class _2(object):
    """description of class"""


    
def getcp(pokemon, uplevel, cp_multiplier):
    org_level = pokemon.level
    attack = pokemon.attack
    defense = pokemon.defense
    stamina = pokemon.stamina

    if uplevel == 0:
        return 0
    res = 0
    for u in xrange(uplevel):
        m = cp_multiplier.get_multiplier_for_level(org_level + u) - cp_multiplier.get_multiplier_for_level(org_level + u - 1)
        res += attack * sqrt(defense*stamina) * m * m / 10.0
    return res

def find_maximum_cp_gained(num_pow_ups, pokemon_list, cp_multiplier):
    dp = [[0.0]*len(pokemon_list)] * (num_pow_ups + 1)
    # print dp
    #for pidx in xrange(len(pokemon_list)):
    #    pokemon = pokemon_list[pidx]
    #    dp[0][pidx] = getcp(pokemon,1, cp_multiplier)
    
    for u in xrange(1,num_pow_ups + 1):
        dp[u][0] = dp[u-1][0] + getcp(pokemon_list[0], u, cp_multiplier)
        for pidx in xrange(1, len(pokemon_list)):
            pokemon = pokemon_list[pidx]
            dp[u][pidx] = 0
            for current_up_num in xrange(1, u + 1):
                cur_res = getcp(pokemon, current_up_num) + dp[u - current_up_num][pidx - 1]
                dp[u][pidx] = max(cur_res, dp[u][pidx])
    return dp[-1][-1]