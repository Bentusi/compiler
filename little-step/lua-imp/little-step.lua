#! /usr/local/bin/lua

-- ============================================================================
-- Expr
-- ============================================================================
Expr = {}
function Expr:new()
	local self = {}
	setmetatable(self, Expr)
	self.__index = self
	return self
end

-- ============================================================================
-- Num
-- ============================================================================
Num = {}
setmetatable(Num, Expr)
Num.__index = Num
function Num:new(init)
    local self = Expr:new()
    setmetatable(self, Num)
    self.v = init
    return self
end

function Num:to_s()
    return string.format("%s", self.v)
end

function Num:reduceable()
    return false
end

function Num:reduce(env)
    return self
end

function Num:value()
    return self.v
end

-- ============================================================================
-- Bool
-- ============================================================================
Bool = {}
setmetatable(Bool, Expr)
Bool.__index = Bool
function Bool:new(init)
    local self = Expr:new()
    setmetatable(self, Bool)
    self.v = init
    return self
end

function Bool:to_s()
    return string.format("%s", self.v)
end

function Bool:reduceable()
    return false
end

function Bool:reduce(env)
    return self
end

function Bool:value()
    return self.v
end

-- ============================================================================
-- Add
-- ============================================================================
Add = {}
setmetatable(Add, Expr)
Add.__index = Add
function Add:new(left, right)
    local self = Expr:new()
	setmetatable(self, Add)
    self.l = left
    self.r = right
    return self
end

function Add:to_s()
    return "(" .. self.l:to_s() .. "+" .. self.r:to_s() .. ")"
end

function Add:reduceable()
    return true
end

function Add:reduce(env)
    if self.l:reduceable() then
        return Add:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Add:new(self.l, self.r:reduce(env))
    else
        return Num:new(self.l:value() + self.r:value())
    end
end

-- ============================================================================
-- Mns
-- ============================================================================
Mns = {}
setmetatable(Mns, Expr)
Mns.__index = Mns
function Mns:new(left, right)
    local self = Expr:new()
	setmetatable(self, Mns)
    self.l = left
    self.r = right
    return self
end

function Mns:to_s()
    return "(" .. self.l:to_s() .. "-" .. self.r:to_s() .. ")"
end

function Mns:reduceable()
    return true
end

function Mns:reduce(env)
    if self.l:reduceable() then
        return Mns:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Mns:new(self.l, self.r:reduce(env))
    else
        return Num:new(self.l:value() - self.r:value())
    end
end

-- ============================================================================
-- Mult
-- ============================================================================
Mult = {}
setmetatable(Mult, Expr)
Mult.__index = Mult
function Mult:new(left, right)
    local self = Expr:new()
	setmetatable(self, Mult)
    self.l = left
    self.r = right
    return self
end

function Mult:to_s()
    return "(" .. self.l:to_s() .. "*" .. self.r:to_s() .. ")"
end

function Mult:reduceable()
    return true
end

function Mult:reduce(env)
    if self.l:reduceable() then
        return Mult:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Mult:new(self.l, self.r:reduce(env))
    else
        return Num:new(self.l:value() * self.r:value())
    end
end

-- ============================================================================
-- Div
-- ============================================================================
Div = {}
setmetatable(Div, Expr)
Div.__index = Div
function Div:new(left, right)
    local self = Expr:new()
	setmetatable(self, Div)
    self.l = left
    self.r = right
    return self
end

function Div:to_s()
    return "(" .. self.l:to_s() .. "/" .. self.r:to_s() .. ")"
end

function Div:reduceable()
    return true
end

function Div:reduce(env)
    if self.l:reduceable() then
        return Div:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Div:new(self.l, self.r:reduce(env))
    else
        return Num:new(self.l:value() / self.r:value())
    end
end

-- ============================================================================
-- Lt
-- ============================================================================
Lt = {}
setmetatable(Lt, Expr)
Lt.__index = Lt
function Lt:new(left, right)
    local self = Expr:new()
	setmetatable(self, Lt)
    self.l = left
    self.r = right
    return self
end

function Lt:to_s()
    return "(" .. self.l:to_s() .. "<" .. self.r:to_s() .. ")"
end

function Lt:reduceable()
    return true
end

function Lt:reduce(env)
    if self.l:reduceable() then
        return Lt:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Lt:new(self.l, self.r:reduce(env))
    else
        return Bool:new(self.l:value() < self.r:value())
    end
end

-- ============================================================================
-- Le
-- ============================================================================
Le = {}
setmetatable(Le, Expr)
Le.__index = Le
function Le:new(left, right)
    local self = Expr:new()
	setmetatable(self, Le)
    self.l = left
    self.r = right
    return self
end

function Le:to_s()
    return "(" .. self.l:to_s() .. "<=" .. self.r:to_s() .. ")"
end

function Le:reduceable()
    return true
end

function Le:reduce(env)
    if self.l:reduceable() then
        return Le:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Le:new(self.l, self.r:reduce(env))
    else
        return Bool:new(self.l:value() <= self.r:value())
    end
end

-- ============================================================================
-- Gt
-- ============================================================================
Gt = {}
setmetatable(Gt, Expr)
Gt.__index = Gt
function Gt:new(left, right)
    local self = Expr:new()
	setmetatable(self, Gt)
    self.l = left
    self.r = right
    return self
end

function Gt:to_s()
    return "(" .. self.l:to_s() .. ">" .. self.r:to_s() .. ")"
end

function Gt:reduceable()
    return true
end

function Gt:reduce(env)
    if self.l:reduceable() then
        return Gt:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Gt:new(self.l, self.r:reduce(env))
    else
        return Bool:new(self.l:value() > self.r:value())
    end
end

-- ============================================================================
-- Ge
-- ============================================================================
Ge = {}
setmetatable(Ge, Expr)
Ge.__index = Ge
function Ge:new(left, right)
    local self = Expr:new()
	setmetatable(self, Ge)
    self.l = left
    self.r = right
    return self
end

function Ge:to_s()
    return "(" .. self.l:to_s() .. ">=" .. self.r:to_s() .. ")"
end

function Ge:reduceable()
    return true
end

function Ge:reduce(env)
    if self.l:reduceable() then
        return Ge:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Ge:new(self.l, self.r:reduce(env))
    else
        return Bool:new(self.l:value() > self.r:value())
    end
end

-- ============================================================================
-- Eq
-- ============================================================================
Eq = {}
setmetatable(Eq, Expr)
Eq.__index = Eq
function Eq:new(left, right)
    local self = Expr:new()
	setmetatable(self, Eq)
    self.l = left
    self.r = right
    return self
end

function Eq:to_s()
    return "(" .. self.l:to_s() .. "==" .. self.r:to_s() .. ")"
end

function Eq:reduceable()
    return true
end

function Eq:reduce(env)
    if self.l:reduceable() then
        return Eq:new(self.l:reduce(env), self.r)
    elseif self.r:reduceable() then
        return Eq:new(self.l, self.r:reduce(env))
    else
        return Bool:new(self.l:value() == self.r:value())
    end
end

-- ============================================================================
-- Null
-- ============================================================================
Null = {}
setmetatable(Null, Expr)
Null.__index = Null
function Null:new()
    local self = Expr:new()
	setmetatable(self, Null)
    return self
end

function Null:to_s()
    return "do-nothing"
end

function Null:reduceable()
    return false
end

function Null:reduce(env)
    return self
end

-- ============================================================================
-- Var
-- ============================================================================
Var = {}
setmetatable(Var, Expr)
Var.__index = Var
function Var:new(name)
    local self = Expr:new()
	setmetatable(self, Var)
    self.n = name or ""
    return self
end

function Var:to_s()
    return self.n
end

function Var:reduceable()
    return true
end

function Var:reduce(env)
    return env[self.n]
end

-- ============================================================================
-- Asgn
-- ============================================================================
Asgn = {}
setmetatable(Asgn, Expr)
Asgn.__index = Asgn
function Asgn:new(name, expr)
    local self = Expr:new()
	setmetatable(self, Asgn)
    self.n = name or ""
    self.expr = expr or Num:new(0)
    return self
end

function Asgn:to_s()
    return "(" .. self.n .. "=" .. self.expr:to_s() .. ")"
end

function Asgn:reduceable()
    return true
end

function Asgn:reduce(env)
    if self.expr:reduceable() then
        return Asgn:new(self.n, self.expr:reduce(env))
    else
        env[self.n] = self.expr
        return Null:new()
    end
end

-- ============================================================================
-- If
-- ============================================================================
If = {}
setmetatable(If, Expr)
If.__index = If
function If:new(cond, t, f)
    local self = Expr:new()
	setmetatable(self, If)
    self.c = cond or Null:new()
    self.t = t or Null:new()
    self.f = f or Null:new()
    return self
end

function If:to_s()
    return "IF " .. self.c:to_s() .. " THEN " .. self.t:to_s() .. " ELSE " .. self.f:to_s()
end

function If:reduceable()
    return true
end

function If:reduce(env)
    if self.c:reduceable() then
        return If:new(self.c:reduce(env), self.t, self.f)
    else
        if self.c:value() == true then
            return self.t
        else
            return self.f
        end
    end
end

-- ============================================================================
-- Con
-- ============================================================================
Con = {}
setmetatable(Con, Expr)
Con.__index = Con
function Con:new(f, s)
    local self = Expr:new()
	setmetatable(self, Con)
    self.f = f or Null:new()
    self.s = s or Null:new()
    return self
end

function Con:to_s()
    return self.f:to_s() .. ";" .. self.s:to_s()
end

function Con:reduceable()
    return true
end

function Con:reduce(env)
    if self.f:reduceable() then
        return Con:new(self.f:reduce(env), self.s)
    else
        return self.s
    end
end

-- ============================================================================
-- While
-- ============================================================================
While = {}
setmetatable(While, Expr)
While.__index = While
function While:new(cond, body)
    local self = Expr:new()
	setmetatable(self, While)
    self.c = cond or Null:new()
    self.b = body or Null:new()
    return self
end

function While:to_s()
    return "WHILE " .. self.c:to_s() .. " THEN " .. self.b:to_s() .. " END"
end

function While:reduceable()
    return true
end

function While:reduce(env)
    if self.c:reduceable() then
        return If:new(self.c, Con:new(self.b, self), Null:new())
    else
        return Null:new()
    end
end

-- ============================================================================
-- 
-- ============================================================================
function env_to_s(env)
    local str = "{"
    for key, value in pairs(env) do
        str = str .. string.format("(%s=%s)", key, value:to_s())
    end
    return str .. "}"
end

function VM(expr, env)
    print(expr:to_s() .. ", " .. env_to_s(env))
    while expr:reduceable() do
        expr = expr:reduce(env)
        print(expr:to_s() .. ", " .. env_to_s(env))
    end
end

-- ============================================================================
-- 
-- ============================================================================
function main()
    -- local d = Div:new(
    --     Num:new(2.1),
    --     Add:new(Num:new(0), Num:new(0)))
    -- VM(d)

    local env = {}
    env["x"] = Num:new(0)

    local b = 
    While:new( Lt:new(Var:new("x"), Num:new(4.0)),
            Asgn:new("x", Add:new(Var:new("x"), Num:new(1.0))))

    VM(b, env)
end

main()
