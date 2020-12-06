
(***********************************************************)
(*                                                         *)
(***********************************************************)
class virtual expr =
object (self)
    method virtual to_s : string
    method virtual reduceable : bool
    method virtual reduce : expr
end

(***********************************************************)
(*                                                         *)
(***********************************************************)
class num (init:int) =
object (self)
    inherit expr
    val v:int = init
    method reduceable = false
    method to_s   = string_of_int v
    method reduce = (self :> expr)
    method eval   = v
end

(***********************************************************)
(*                                                         *)
(***********************************************************)
class add (left:expr) (right:expr) =
object(self)
    inherit expr
    method reduceable = true
    method reduce     = 
        if left#reduceable then
            new add left#reduce right
        else if right#reduceable then
            new add left right#reduce
        else
            (* (new num 12 :> expr) *)
            (new num ((left:>num)#eval + (right:>num)#eval) :> expr)
    method to_s       = "(" ^ left#to_s ^ " + " ^ right#to_s ^ ")";
    method eval   = (new num ((left:>num)#eval + (right:>num)#eval) :> expr)
end

(***********************************************************)
(*                                                         *)
(***********************************************************) 
let a = new num 1;;
let b = new num 11;;

let c = new add (a:>expr) (b:>expr);;
let d = c#reduce;;
print_string d#to_s;;