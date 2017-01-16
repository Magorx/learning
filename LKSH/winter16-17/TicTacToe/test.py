if board[i[j + 1][0]][i[j + 1][1]] == symb:
                                if board[i[2][0]][i[2][1]] == 0:
                                    return (self.inf, tuple(i[2][0],i[2][1]))
                            elif board[i[2][0]][i[2][1]] == 0:
                                return (self.inf, i[j + 1][0],i[j + 1][1])

                            if board[i[j + 1][0]][i[j + 1][1]] == self.player_type:
                                if symb == self.player_type:
                                    return (self.inf, tuple(i[0][0],i[0][1]))
                                counter = 0
                                break