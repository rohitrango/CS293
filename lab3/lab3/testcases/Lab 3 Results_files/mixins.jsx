var SavedStatusMixin={componentWillMount:function(){this.setState({savedStatus:'saved'});},checkFor:function(status){return this.state.savedStatus==status;},changeTo:function(status){this.setState({savedStatus:status},this.onSavedStatusUpdate);},savedIf:function(check){this.changeTo(check?'saved':'unsaved');},selectBySavedStatus:function(options){return options[this.state.savedStatus];},isSaved:function(){return this.checkFor('saved');},isUnsaved:function(){return this.checkFor('unsaved');},isSaving:function(){return this.checkFor('saving');},toSaved:function(){this.changeTo('saved');},toSaving:function(){this.changeTo('saving');},toUnsaved:function(){this.changeTo('unsaved');}};var BackgroundTransitionMixin={getBackgroundTransitionStyle:function(colors,noTransition,duration){if(noTransition)return{};if(!colors)colors={};if(!duration)duration=1000;transition='background-color '+duration+'ms linear';style={WebkitTransition:transition,MozTransition:transition,OTransition:transition,MsTransition:transition,'transition':transition}
if(!colors.unsaved)colors.unsaved='#e4f2ff';if(!colors.saved)colors.saved='#ffffff';if(!colors.saving)colors.saving='#f0f8ff';style.backgroundColor=this.selectBySavedStatus(colors);return style;}}
var StyleTransitionMixin={getStyleTransition:function(property,duration){if(!duration)duration=1000;transition=property+' '+duration+'ms linear';return{WebkitTransition:transition,MozTransition:transition,OTransition:transition,MsTransition:transition,'transition':transition};}}

var MathJaxMixin = {
    componentDidMount: function (root) {
        MathJax.Hub.Queue(["Typeset",MathJax.Hub,root]);
    },
    componentDidUpdate: function (props,state,root) {
        MathJax.Hub.Queue(["Typeset",MathJax.Hub,root]);
    }
}