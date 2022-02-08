require 'set'
require 'calculator'

class BinaryNode
  attr_reader :left, :right
  
  def initialize(left,right)
    @left = left
    @right = right
  end
end
   
class UnaryNode
  attr_reader :subTree
   
  def initialize subTree
    @subTree = subTree
  end
end

class AddNode < BinaryNode
  def initialize(left, right)
    super left,right
  end
   
  def evaluate
    @left.evaluate + @right.evaluate
  end
end

class SubNode < BinaryNode
  def initialize left, right
    super left,right
  end
   
  def evaluate 
    @left.evaluate - @right.evaluate
  end
end

class TimesNode < BinaryNode
  def initialize left, right
    super left,right
  end
   
  def evaluate 
    @left.evaluate * @right.evaluate
  end
end

class DivideNode < BinaryNode
  def initialize left, right
    super left,right
  end
   
  def evaluate
    if @right.evaluate == 0.0 then
      raise Inf
    else
      @left.evaluate / @right.evaluate
    end
  end
end

class ModuleNode < BinaryNode
  def initialize left, right
    super left,right
  end

  def evaluate
    @left.evaluate.modulo(@right.evaluate)
  end
end

class NumNode 
  def initialize(num)
    @num = num
  end
   
  def evaluate
    @num
  end
end

class EolNode
  def initialize(eol)
    @eol = eol
  end

  def evaluate
    @eol
  end
end

class IDNode
  attr_accessor :ro
  def initialize(ro)
    @ro = ro
  end

  def evaluate
    pt = $calc.potatos[ro]
    pt
  end
end

class NonNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    @subTree.evaluate * -1.0
  end
end

class StoreNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    $calc.memory = @subTree.evaluate
    $calc.memory
  end
end

class PlusNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    $calc.memory = $calc.memory + @subTree.evaluate
    $calc.memory
  end
end

class MinusNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    $calc.memory = $calc.memory - @subTree.evaluate
    $calc.memory
  end
end

class RecallNode
  def initialize; end

  def evaluate
    $calc.memory
  end
end

class ClearNode
  def initialize; end

  def evaluate
    $calc.memory = 0.0
  end
end

class AssignationNode < UnaryNode
  attr_accessor :pato
  def initialize(sub, pato)
    super sub
    
    @pato = pato
  end

  def evaluate
    co = @subTree.evaluate
    $calc.potatos.store(@pato, co)
    return co
  end
end

class ABSNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    @subTree.evaluate.abs
  end
end

class SINNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    Math.sin(@subTree.evaluate)
  end
end

class COSNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    Math.cos(@subTree.evaluate)
  end
end

class TANNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    Math.tan(@subTree.evaluate)
  end
end

class EXPNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    Math.exp(@subTree.evaluate)
  end
end

class LOGNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    Math.log(@subTree.evaluate)
  end
end

class SQRTNode < UnaryNode
  def initialize sub
    super sub
  end

  def evaluate
    if @subTree.evaluate < 0.0 then
      raise Nan
    else
      Math.sqrt(@subTree.evaluate)
    end
  end
end
    
