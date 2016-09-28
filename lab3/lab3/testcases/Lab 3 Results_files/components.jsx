/** @jsx React.DOM */

var WmdTextarea = React.createClass({
    componentDidMount: function(root) {
        $(root).wmd();
    },

    render: function() {
        return this.transferPropsTo(
            <textarea class="form-control wmd-input" />
        )
    }
});


var UserLink = React.createClass({
    render: function() {
        if(this.props.data == null) {
            return (<span><strong>Anonymous</strong></span>);
        }

        return (
            <a href={"/profile/" + this.props.data.username}>
                <strong>
                {this.props.data.first_name + ' ' + this.props.data.last_name}
                </strong>
            </a>
        );
    }
});


var DynamicDateTime = React.createClass({
    //props: time(date-time format), refreshInterval(seconds)
    getInitialState: function() {
        var time = moment(new Date(this.props.time)).fromNow();
        return {"time": time};
    },

    updateTime: function() {
        var time = moment(new Date(this.props.time)).fromNow();
        this.setState({"time": time});
    },

    componentDidMount: function() {
        this.updateTime();
        var intervalId = window.setInterval(this.updateTime, this.props.refreshInterval);
        this.setState({"intervalId": intervalId})
    },

    componentWillUnmount: function() {
        window.clearInterval(this.state.intervalId);
    },

    render: function() {
        return (
            <span>{this.state.time}</span>
        )
    }
});

var LoadingBar = React.createClass({
    render: function() {
        var innerText = "Loading ...";
        if(this.props.innerText)
            innerText = this.props.innerText;
        return (
            <div class="progress progress-striped active">
                <div class="progress-bar loading-bar" role="progressbar">
                    {innerText}
                </div>
            </div>
        )
    }
});




/*  Ajax Image Uploader
    Props:
    url: URL to which the image should be sent
    noBackgroundTransition: Boolean, if this is set to true, then there
        are no background transitions based on the saved status
    BackTransitionColors: Pass an object of the following form:
        {
            'saved': '#color1'.
            'saving': '#color2'.
            'unsaved': '#color3'
        }
        These will be used for background transitions (see BackgroundTransitionMixin)

*/
var ImageUploader = React.createClass({
    mixins: [SavedStatusMixin, BackgroundTransitionMixin, StyleTransitionMixin],

    getInitialState: function() {
        return {
            image: this.props.image
        };
    },

    getDefaultProps: function() {
        return {
            BackgroundTransitionColors: {},
            noBackgroundTransition: false,
            name: 'image',
            isFile: false
        };
    },

    showProgressBar: function() {
        this.refs.imageUploadProgressBar.getDOMNode().style.display = 'block';
    },

    hideProgressBar: function() {
        this.refs.imageUploadProgressBar.getDOMNode().style.display = 'none';
        this.refs.imageUploadProgress.getDOMNode().style.width = 0;
    },

    progressHandlingFunction: function(event) {
        if(event.lengthComputable) {
            percent = 100*(event.loaded/event.total)+"%";
            this.refs.imageUploadProgress.getDOMNode().style.width = percent;
        }
    },

    changeImage: function() {
        var getExtension = function (filename) {
            var parts = filename.split('.');
            return parts[parts.length - 1];
        };

        var isImage = function (filename) {
            var ext = getExtension(filename);
            switch (ext.toLowerCase()) {
            case 'jpg':
            case 'gif':
            case 'bmp':
            case 'png':
                return true;
            }
            return false;
        };

        var formData = new FormData(this.refs.imageForm.getDOMNode());

        if (!this.props.isFile){
            if(!isImage(this.refs.imageUploadInput.getDOMNode().files[0].name)) {
                display_global_message("Invalid File Format", "error");
                $(this.refs.resetImageUploader.getDOMNode()).click();
                return false;
            }
        }

        ajax_custom_request({
            url: this.props.url,
            type: 'PATCH',
            data: formData,
            beforeSend: function(xhr, settings){
                this.toSaving();
                this.showProgressBar();
            }.bind(this),
            success: function(response){
                if (this.props.isFile){
                    this.setState({image: response[this.props.name]});
                }
                else{
                    this.setState({image: response[this.props.name]});
                }
                this.toSaved();
                setTimeout(function(){
                    this.hideProgressBar();
                    $(this.refs.resetImageUploader.getDOMNode()).click();
                }.bind(this), 1000);

            }.bind(this),
            error: function(xhr, textStatus, errorThrown){
                msg = "Unable to upload image";
                if (xhr.responseText) msg += " - " + jQuery.parseJSON(xhr.responseText).detail;
                display_global_message(msg , "error");
                this.hideProgressBar();
                this.toUnsaved();
            }.bind(this),
            progressFunction: this.progressHandlingFunction
        });
    },

    onSavedStatusUpdate: function() {
        if (this.isSaved() && this.props.changeCallback)
            this.changeCallback(this.state.image);
    },

    render: function() {
        var saveBtnClass = this.selectBySavedStatus({
            'saved': 'btn-success disabled',
            'saving': 'btn-primary disabled',
            'unsaved': 'btn-primary'
        });

        var saveBtnText = this.selectBySavedStatus({
            'saved': 'Saved',
            'saving': 'Saving..',
            'unsaved': 'Save'
        });

        var change_remove_revert_buttons = null;

        if(this.props.is_editable) {
            change_remove_revert_buttons = (
                <div>
                    <span class="btn btn-primary btn-file">
                        <span class="fileinput-new">Change</span>
                        <span class="fileinput-exists">Change</span>
                        <input type="file" name={this.props.name} ref="imageUploadInput" onChange={this.toUnsaved}/>
                    </span>
                    <button type="button" class="btn btn-danger fileinput-new">Remove</button>
                    <button type="button" class={"btn fileinput-exists " + saveBtnClass} onClick={this.changeImage}>
                        {saveBtnText}
                    </button>
                    <button type="button" class="btn btn-warning fileinput-exists"
                            data-dismiss="fileinput" ref="resetImageUploader"
                            onClick={this.toSaved}>
                        Revert
                    </button>
                </div>
            );
        }

        return(
            <div style={this.getBackgroundTransitionStyle(this.props.BackgroundTransitionColors,
            this.props.noBackgroundTransition)}>
                <form enctype="multipart/form-data" ref="imageForm">
                    <div class="fileinput fileinput-new image-upload-box" data-provides="fileinput">
                        <div class="fileinput-new thumbnail">
                            {this.props.isFile ?
                                <a href={this.state.image} target="_blank">Slides</a>
                                : <img src={this.state.image} alt="Unable to display image"/>
                            }
                        </div>
                        <div class="fileinput-preview fileinput-exists thumbnail"></div>
                        {change_remove_revert_buttons}
                        <div class="progress fileinput-exists" ref="imageUploadProgressBar" style={{display: "none"}}>
                            <div class="progress-bar progress-bar-success"
                                 role="progressbar"
                                 ref="imageUploadProgress"
                                 style={{width: 0}}>
                                <span class="sr-only">60% Complete</span>
                            </div>
                        </div>
                    </div>
                </form>
            </div>
        );
    }
});
