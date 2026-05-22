# Chess Game Roadmap

## Phase 1 — Foundation ✅
- [x] Piece base class (color, shorthand, shared utilities)
- [x] All 6 piece subclasses
- [x] Move validation (`isValidMove`) for all pieces
- [x] Path obstruction checking (`willHit`)
- [x] Capture validation (`canTake`)
- [x] Board array and initialization (`setup`)
- [x] Board display (`printBoard`)
- [x] Piece `toString` and `<<` operator
- [x] Header documentation

## Phase 2 — Core Game Loop
- [x] Implement `move()` for all pieces — actually update the board array
- [ ] Basic game loop in `main` — repeatedly prompt for input until game over
- [ ] User input parsing — accept a source and destination square (e.g. `e2 e4`)
- [ ] Turn tracking — alternate between white and black each move
- [ ] Reject moves for the wrong color

## Phase 3 — Check & Game Over
- [ ] Implement `isSafe()` — detect if a given square is under attack
- [ ] Reject any move that leaves your own king in check
- [ ] Checkmate detection — no legal moves and king is in check
- [ ] Stalemate detection — no legal moves and king is not in check

## Phase 4 — Special Moves
- [x] Castling — king and rook swap, with conditions (neither moved, no pieces between, king not in/through check)
- [ ] En passant — pawn captures a pawn that just moved two squares
- [ ] Pawn promotion — replace pawn with chosen piece upon reaching the back rank

## Phase 5 — Polish (Optional)
- [ ] Move history / algebraic notation output
- [ ] Draw conditions (50-move rule, threefold repetition, insufficient material)
