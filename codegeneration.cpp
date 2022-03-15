#include "codegeneration.hpp"

// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
	std::cout<<"    .data"<<std::endl;
	std::cout<<"    printstr: .asciz \"%d\\n\""<<std::endl;
	std::cout<<"    .text"<<std::endl;
	std::cout<<"    .globl Main_main"<<std::endl;
	node->visit_children(this);
}


void CodeGenerator::visitClassNode(ClassNode* node) {
    currentClassName=node->identifier_1->name;
    currentClassInfo=(*classTable)[node->identifier_1->name];
    node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    currentMethodName=node->identifier->name;
	currentMethodInfo=(*currentClassInfo.methods)[node->identifier->name];
	node->visit_children(this);
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    std::cout<<currentClassName<<"_"<<currentMethodName<<":"<< std::endl;
    std::cout<<"    push %ebp" <<std::endl;
	std::cout<<"    mov %esp, %ebp" <<std::endl;
	std::cout<<"    sub $"<<currentMethodInfo.localsSize<<", %esp"<<std::endl;
	node->visit_children(this);
	std::cout<<"    add $" <<currentMethodInfo.localsSize<<", %esp"<<std::endl;
    std::cout<<"    mov %ebp, %esp"<<std::endl;
    std::cout<<"    pop %ebp"<<std::endl;
	std::cout<<"    ret"<<std::endl;
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    node->visit_children(this);
	std::cout<<"    pop %eax"<<std::endl;
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    node->visit_children(this);
    
    // check if local or not     
    // first check if theres id2
    std::cout << "    pop %eax" << std::endl;
    int offset = 0; 
    
    ClassInfo current_currentClassInfo;
    
    if (node->identifier_2 == NULL) {
        // check if id_1 is a variable
        if ((*(currentMethodInfo.variables)).find(node->identifier_1->name) != 
            (*(currentMethodInfo.variables)).end()) {
            offset = (*(currentMethodInfo.variables))[node->identifier_1->name].offset;
    
        } else {
            // it could be part of superclass of currentClass
            // offset = the offset of the variable in the superclass + currentClassInfo.membersSize * 4
            
            current_currentClassInfo = currentClassInfo;
            while (1) {
                //current_currentClassInfo = (*classTable)[current_currentClassInfo.superClassName];
                if ((*(current_currentClassInfo.members)).find(node->identifier_1->name) != 
                    (*(current_currentClassInfo.members)).end()) {
                    offset += (*(current_currentClassInfo.members))[node->identifier_1->name].offset;
                    break;
                } 
                else {
                    offset += current_currentClassInfo.membersSize *4; 
                    current_currentClassInfo = (*classTable)[current_currentClassInfo.superClassName];
                }
            }
        }
        std::cout<<"    move %eax, " << offset << "($ebp)" << std::endl;
    }
    // if we have id_2, then we are assigning to a member of a local class variable
    // this means that we need to go into the pointer.... how?
    
    
    

}




void CodeGenerator::visitCallNode(CallNode* node) {
    node->visit_children(this);
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    node->expression->accept(this);
    int trueL = nextLabel();
    int elseL= nextLabel();
    int exitL= nextLabel();
    
	std::cout<<"    pop %eax"<<std::endl;
	std::cout<<"    mov $1, %edx"<<std::endl;
	std::cout<<"    cmp %eax, %edx"<<std::endl;
	std::cout<<"    je label_" << trueL<<std::endl;
    std::cout<<"    jmp label_"<<elseL<<std::endl;

    std::cout<<"    label_"<<trueL<<":"<<std::endl;
    //accept for true
    if (node->statement_list_1) {
        std::list<StatementNode*>::iterator i = node->statement_list_1->begin();
        while(i!=node->statement_list_1->end()) {
            (*i)->accept(this);
            i++;
        }
    }
    std::cout<<"    jmp label_"<<exitL<<std::endl;

    std::cout<<"    label_" <<elseL<<":"<<std::endl;
    //accept for else
    if (node->statement_list_2) {
        std::list<StatementNode*>::iterator i2 = node->statement_list_2->begin();
        while(i2!=node->statement_list_2->end()) {
            (*i2)->accept(this);
            i2++;
        }
    }
    std::cout<<"    label_"<<exitL<<":"<<std::endl;

}

void CodeGenerator::visitWhileNode(WhileNode* node) {
    int trueL = nextLabel();
    int exitL= nextLabel();
    int restartL = nextLabel();

    std::cout<<"    label_"<<restartL<<":"<<std::endl;
    node->expression->accept(this);

    std::cout<<"    pop %eax"<<std::endl;
	std::cout<<"    mov $1, %edx"<<std::endl;
	std::cout<<"    cmp %eax, %edx"<<std::endl;
	std::cout<<"    je label_"<<trueL<<std::endl;
    std::cout<<"    jmp label_"<<exitL<<std::endl;

    //trueL
    std::cout<<"    label_"<<trueL<<":"<< std::endl;
    if (node->statement_list) {
        std::list<StatementNode*>::iterator i = node->statement_list->begin();
        while(i!=node->statement_list->end()) {
            (*i)->accept(this);
            i++;
        }
    }
    std::cout<<"    jmp label_" <<restartL<<std::endl;
    //exitL
    std::cout<<"    label_"<<exitL<<":"<<std::endl;
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    node->visit_children(this);
    std::cout<<"    push $printstr"<<std::endl;
	std::cout<<"    call printf"<<std::endl;
	std::cout<<"    add $8, %esp"<<std::endl;
}

void CodeGenerator::visitDoWhileNode(DoWhileNode* node) {
    int trueL = nextLabel();
    int restartL = nextLabel();


    std::cout<<"    label_"<<restartL<<":"<<std::endl;
    if (node->statement_list) {
        std::list<StatementNode*>::iterator i = node->statement_list->begin();
        while(i!=node->statement_list->end()) {
            (*i)->accept(this);
            i++;
        }
    }

    node->expression->accept(this);

    std::cout<<"    pop %eax"<<std::endl;
	std::cout<<"    mov $1, %edx"<<std::endl;
	std::cout<<"    cmp %eax, %edx"<<std::endl;
	std::cout<<"    je label_" <<restartL<<std::endl;
}



void CodeGenerator::visitPlusNode(PlusNode* node) {
    node->visit_children(this);
    std::cout<<"    # Plus"<<std::endl;
    std::cout<<"    pop %edx"<<std::endl;
    std::cout<<"    pop %eax"<<std::endl;
    std::cout<<"    add %edx, %eax"<<std::endl;
    std::cout<<"    push %eax"<<std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    node->visit_children(this);
    std::cout<<"    # Minus"<<std::endl;
    std::cout<<"    pop %edx"<<std::endl;
    std::cout<<"    pop %eax"<<std::endl;
    std::cout<<"    sub %edx, %eax"<<std::endl;
    std::cout<<"    push %eax"<<std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    node->visit_children(this);
    std::cout<<"    # Times"<<std::endl;
    std::cout<<"    pop %edx"<<std::endl;
    std::cout<<"    pop %eax"<<std::endl;
    std::cout<<"    imul %edx, %eax"<<std::endl;
    std::cout<<"    push %eax"<<std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    node->visit_children(this);
    std::cout<<"    # Divide"<<std::endl;
    std::cout<<"    pop %ebx"<<std::endl;
    std::cout<<"    pop %eax"<<std::endl;
    std::cout<<"    cdq"<<std::endl;
    std::cout<<"    idiv %ebx"<<std::endl;
    std::cout<<"    push %eax"<<std::endl;
}


void CodeGenerator::visitGreaterNode(GreaterNode* node) {
    node->visit_children(this);
	int trueL = nextLabel();
    int falseL = nextLabel();
    int exitL = nextLabel();
	
	std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    pop %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
    std::cout<<"    jg label_"<<trueL<<std::endl;
    std::cout<<"    jmp label_"<<falseL<<std::endl;
    std::cout<<"    label_"<<trueL<<":"<<std::endl;
	std::cout<<"    push $1"<<std::endl;
    std::cout<<"    jmp label_"<<exitL<<std::endl;
    std::cout<<"    label_"<<falseL<<":"<<std::endl;
	std::cout<<"    push $0"<<std::endl;
    std::cout<<"    label_"<<exitL<<":"<<std::endl;
}

void CodeGenerator::visitGreaterEqualNode(GreaterEqualNode* node) {
    node->visit_children(this);
	int trueL = nextLabel();
    int falseL = nextLabel();
    int exitL = nextLabel();
	
	std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    pop %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
    std::cout<<"    jge label_"<<trueL<<std::endl;
    std::cout<<"    jmp label_"<<falseL<<std::endl;
    std::cout<<"    label_"<<trueL<<":"<<std::endl;
	std::cout<<"    push $1"<<std::endl;
    std::cout<<"    jmp label_"<<exitL<<std::endl;
    std::cout<<"    label_"<<falseL<<":"<<std::endl;
	std::cout<<"    push $0"<<std::endl;
    std::cout<<"    label_"<<exitL<<":"<<std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    node->visit_children(this);
	int trueL = nextLabel();
    int falseL = nextLabel();
    int exitL = nextLabel();
	
	std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    pop %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
    std::cout<<"    je label_"<<trueL<<std::endl;
    std::cout<<"    jmp label_"<<falseL<<std::endl;
    std::cout<<"    label_"<<trueL<<":"<<std::endl;
	std::cout<<"    push $1"<<std::endl;
    std::cout<<"    jmp label_"<<exitL<<std::endl;
    std::cout<<"    label_"<<falseL<<":"<<std::endl;
	std::cout<<"    push $0"<<std::endl;
    std::cout<<"    label_"<<exitL<<":"<<std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
	node->visit_children(this);
	int falseL1 = nextLabel();
	int falseL2 = nextLabel();
	int trueL = nextLabel();
	std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    mov $0, %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
	std::cout<<"    je label_"<<falseL1<<std::endl;
    std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    mov $0, %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
	std::cout<<"    je label_"<<falseL2<<std::endl;
    std::cout<<"    push $1"<<std::endl;
	std::cout<<"    jmp label_"<<trueL<<std::endl;
	std::cout<<"    label_"<<falseL1<<":"<<std::endl;
	std::cout<<"    add $4, %esp"<<std::endl;
	std::cout<<"    label_"<<falseL2<<":"<<std::endl;
	std::cout<<"    push $0"<<std::endl;
	std::cout<<"    label_"<<trueL<<":"<<std::endl;

}

void CodeGenerator::visitOrNode(OrNode* node) {
    node->visit_children(this);
	int trueL1 = nextLabel();
	int trueL2 = nextLabel();
	int falseL = nextLabel();
	std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    mov $0, %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
	std::cout<<"    je label_"<<trueL1<<std::endl;
    std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    mov $0, %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
	std::cout<<"    je label_"<<trueL2<<std::endl;
    std::cout<<"    push $0"<<std::endl;
	std::cout<<"    jmp label_"<<falseL<<std::endl;
	std::cout<<"    label_"<<trueL1<<":"<<std::endl;
	std::cout<<"    add $4, %esp"<<std::endl;
	std::cout<<"    label_"<<trueL2<<":"<<std::endl;
	std::cout<<"    push $1"<<std::endl;
	std::cout<<"    label_"<<falseL<<":"<<std::endl;
}


void CodeGenerator::visitNotNode(NotNode* node) {
    node->visit_children(this);
	int trueL = nextLabel();
	int falseL = nextLabel();
    std::cout<<"    pop %edx"<<std::endl;
	std::cout<<"    mov $1, %eax"<<std::endl;
	std::cout<<"    cmp %edx, %eax"<<std::endl;
	std::cout<<"    je label_"<<trueL<<std::endl;
	std::cout<<"    push $1"<<std::endl;
	std::cout<<"    jmp label_"<<falseL<<std::endl;
	std::cout<<"    label_"<<trueL<<":"<<std::endl;
	std::cout<<"    push $0"<<std::endl;
	std::cout<<"    label_"<<falseL<<":"<<std::endl;

}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    node->visit_children(this);
    std::cout<<"    pop %eax"<<std::endl;
    std::cout<<"    neg %eax"<<std::endl;
    std::cout<<"    push %eax"<<std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
	
}


void CodeGenerator::visitVariableNode(VariableNode* node) {
    
}



void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
	std::cout<<"    push $"<<node->integer->value<<std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
	std::cout<<"    push $"<<node->integer->value<<std::endl;
}



void CodeGenerator::visitNewNode(NewNode* node) {
	std::string curr_class = node->identifier->name;
    int member_size = 0;
	while (curr_class!="") {
		member_size+=(*classTable)[curr_class].membersSize;
		curr_class=(*classTable)[curr_class].superClassName;
	}
	std::cout<<"    push $"<<member_size<<std::endl;
	std::cout<<"    call malloc"<<std::endl;
	std::cout<<"    add $4, %esp"<<std::endl;
	std::cout<<"    push %eax"<<std::endl;


    if((*classTable)[node->identifier->name].methods->count(node->identifier->name)) {
        if (node->expression_list) {
        std::list<ExpressionNode*>::reverse_iterator i=node->expression_list->rbegin();
            while(i!=node->expression_list->rend()) {
                (*i)->accept(this);
                i++;
            }
            std::cout<<"    mov "<<4*node->expression_list->size()<<"(%esp), %eax"<<std::endl;
        }else{
            std::cout<<"    mov "<<"%(esp), %eax"<<std::endl;
        }
        std::cout<<"    push %eax"<<std::endl;
		std::cout<<"    call "<<node->identifier->name<<"_"<<node->identifier->name<<std::endl;
        if (!(node->expression_list)){
            std::cout<<"    add $"<<4<<", %esp"<<std::endl;
        }else{
            std::cout<<"    add $"<<(4*node->expression_list->size())+4<<", %esp"<<std::endl;
        } 
    }
}


void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
