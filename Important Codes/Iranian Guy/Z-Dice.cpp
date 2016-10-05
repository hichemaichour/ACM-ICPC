struct dice{
	int top,button,front,back,left,right;
	dice(){
		top=1;
		button=2;
		front=3;
		back=4;
		left=5;
		right=6;
	}
	dice shift_left(){
		dice ans=*this;
		swap(ans.front,ans.right);
		swap(ans.right,ans.back);
		swap(ans.back,ans.left);
		return(ans);
	}
	dice shift_top(){
		dice ans=*this;
		swap(ans.front,ans.button);
		swap(ans.button,ans.back);
		swap(ans.back,ans.top);
		return(ans);
	}
	dice rotate_left(){
		dice ans=*this;
		swap(ans.top,ans.right);
		swap(ans.right,ans.button);
		swap(ans.button,ans.left);
		return(ans);
	}
	dice shift_right(){
		return(shift_left().shift_left().shift_left());
	}
	dice shift_button(){
		return(shift_top().shift_top().shift_top());
	}
	dice rotate_right(){
		return(rotate_left().rotate_left().rotate_left());
	}
};
